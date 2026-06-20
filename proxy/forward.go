package main

import (
	"bufio"
	"bytes"
	"encoding/binary"
	"io"
	"log"
	"net"
	"strconv"
	"strings"
	"time"
)

func StartForward(config ForwardConfig) {
	ln, err := net.Listen("tcp", config.Listen)
	if err != nil {
		log.Fatalf("Forward: Failed to listen: %v", err)
	}
	log.Printf("Forward: Listening on %s", config.Listen)

	for {
		conn, err := ln.Accept()
		if err != nil {
			continue
		}
		go handleForward(conn)
	}
}

func handleForward(conn net.Conn) {
	var first [1]byte
	if _, err := io.ReadFull(conn, first[:]); err != nil {
		conn.Close()
		return
	}
	if first[0] == 5 {
		handleSocks5(conn)
	} else {
		handleHTTP(conn, first[0])
	}
}

func handleHTTP(conn net.Conn, first byte) {
	defer conn.Close()

	r := bufio.NewReader(io.MultiReader(bytes.NewReader([]byte{first}), conn))

	reqLine, err := r.ReadString('\n')
	if err != nil {
		return
	}
	parts := strings.Fields(reqLine)
	if len(parts) < 2 {
		return
	}
	method := parts[0]

	var host string
	var contentLength int
	var headers []string
	for {
		line, err := r.ReadString('\n')
		if err != nil {
			return
		}
		line = strings.TrimRight(line, "\r\n")
		if line == "" {
			break
		}
		headers = append(headers, line)
		lower := strings.ToLower(line)
		if strings.HasPrefix(lower, "host:") {
			host = strings.TrimSpace(line[5:])
		}
		if strings.HasPrefix(lower, "content-length:") {
			contentLength, _ = strconv.Atoi(strings.TrimSpace(line[15:]))
		}
	}

	if host == "" {
		return
	}
	if !strings.Contains(host, ":") {
		host = net.JoinHostPort(host, "80")
	}

	dest, err := net.DialTimeout("tcp", host, 10*time.Second)
	if err != nil {
		return
	}
	defer dest.Close()

	if method == "CONNECT" {
		conn.Write([]byte("HTTP/1.1 200 Connection Established\r\n\r\n"))
		go io.Copy(dest, conn)
		io.Copy(conn, dest)
		return
	}

	var buf bytes.Buffer
	buf.WriteString(reqLine)
	for _, h := range headers {
		buf.WriteString(h + "\r\n")
	}
	buf.WriteString("\r\n")
	if _, err := dest.Write(buf.Bytes()); err != nil {
		return
	}
	if contentLength > 0 {
		io.CopyN(dest, r, int64(contentLength))
	}

	io.Copy(conn, dest)
}

func handleSocks5(conn net.Conn) {
	defer conn.Close()

	buf := make([]byte, 262)

	io.ReadFull(conn, buf[:2])
	io.ReadFull(conn, buf[:buf[1]])
	conn.Write([]byte{5, 0})

	io.ReadFull(conn, buf[:4])

	var host string
	var n int

	switch buf[3] {
	case 1:
		io.ReadFull(conn, buf[:4])
		host = net.IP(buf[:4]).String()
		n = 4
	case 3:
		io.ReadFull(conn, buf[:1])
		n = int(buf[0])
		io.ReadFull(conn, buf[:n])
		host = string(buf[:n])
	case 4:
		io.ReadFull(conn, buf[:16])
		host = net.IP(buf[:16]).String()
		n = 16
	default:
		return
	}

	io.ReadFull(conn, buf[:2])
	port := binary.BigEndian.Uint16(buf[:2])

	dest, err := net.DialTimeout("tcp", net.JoinHostPort(host, strconv.Itoa(int(port))), 10*time.Second)
	if err != nil {
		return
	}
	defer dest.Close()

	conn.Write([]byte{5, 0, 0, 1, 0, 0, 0, 0, 0, 0})

	go io.Copy(dest, conn)
	io.Copy(conn, dest)
}
