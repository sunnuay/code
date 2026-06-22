package main

import (
	"bufio"
	"bytes"
	"encoding/binary"
	"io"
	"log"
	"net"
	"net/http"
	"strconv"
)

func StartForward(config ForwardConfig) {
	listener, err := net.Listen("tcp", config.Listen)
	if err != nil {
		log.Fatalf("Forward: Failed to listen: %v", err)
	}
	log.Printf("Forward: Listening on %s", config.Listen)

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Printf("Forward: Failed to accept: %v", err)
			continue
		}
		go handleConn(conn)
	}
}

type readerConn struct {
	net.Conn
	reader io.Reader
}

func (conn *readerConn) Read(p []byte) (int, error) {
	return conn.reader.Read(p)
}

func handleConn(conn net.Conn) {
	defer conn.Close()

	var buf [1]byte

	if _, err := io.ReadFull(conn, buf[:]); err != nil {
		return
	}

	wrapped := &readerConn{
		Conn:   conn,
		reader: io.MultiReader(bytes.NewReader(buf[:]), conn),
	}

	if buf[0] == 0x05 {
		handleSocks5(wrapped)
	} else {
		handleHTTP(wrapped)
	}
}

func handleSocks5(conn net.Conn) {
	defer conn.Close()

	var buf [257]byte

	if _, err := io.ReadFull(conn, buf[:2]); err != nil {
		return
	}
	if _, err := io.ReadFull(conn, buf[:buf[1]]); err != nil {
		return
	}
	conn.Write([]byte{0x05, 0x00})

	if _, err := io.ReadFull(conn, buf[:4]); err != nil || buf[1] != 0x01 {
		return
	}

	var host string
	switch buf[3] {
	case 0x01:
		if _, err := io.ReadFull(conn, buf[:6]); err != nil {
			return
		}
		host = net.JoinHostPort(net.IP(buf[:4]).String(), strconv.Itoa(int(binary.BigEndian.Uint16(buf[4:6]))))
	case 0x04:
		if _, err := io.ReadFull(conn, buf[:18]); err != nil {
			return
		}
		host = net.JoinHostPort(net.IP(buf[:16]).String(), strconv.Itoa(int(binary.BigEndian.Uint16(buf[16:18]))))
	case 0x03:
		if _, err := io.ReadFull(conn, buf[:1]); err != nil {
			return
		}
		l := buf[0] // l <= 255
		if _, err := io.ReadFull(conn, buf[:l+2]); err != nil {
			return
		}
		host = net.JoinHostPort(string(buf[:l]), strconv.Itoa(int(binary.BigEndian.Uint16(buf[l:l+2]))))
	default:
		return
	}

	target, err := net.Dial("tcp", host)
	if err != nil {
		conn.Write([]byte{0x05, 0x01, 0x00, 0x01, 0, 0, 0, 0, 0, 0})
		return
	} else {
		conn.Write([]byte{0x05, 0x00, 0x00, 0x01, 0, 0, 0, 0, 0, 0})
	}
	defer target.Close()

	relay(conn, target)
}

func handleHTTP(conn net.Conn) {
	defer conn.Close()

	req, err := http.ReadRequest(bufio.NewReader(conn))
	if err != nil {
		return
	}

	host := req.Host
	if _, _, err := net.SplitHostPort(host); err != nil {
		host = net.JoinHostPort(host, "80")
	}

	target, err := net.Dial("tcp", host)
	if err != nil {
		return
	}
	defer target.Close()

	if req.Method == http.MethodConnect {
		conn.Write([]byte("HTTP/1.1 200 Connection Established\r\n\r\n"))
	} else {
		req.Write(target)
	}

	relay(conn, target)
}

func relay(a, b net.Conn) {
	go io.Copy(b, a)
	io.Copy(a, b)
}
