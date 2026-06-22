package main

import (
	"bytes"
	"io"
	"log"
	"net"
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

	var b [1]byte
	if _, err := io.ReadFull(conn, b[:]); err != nil {
		return
	}

	wrapped := &readerConn{
		Conn:   conn,
		reader: io.MultiReader(bytes.NewReader(b[:]), conn),
	}

	if b[0] == 0x05 {
		handleSocks(wrapped)
	} else {
		handleHTTP(wrapped)
	}
}

func handleSocks(conn net.Conn) {
	defer conn.Close()
}

func handleHTTP(conn net.Conn) {
	defer conn.Close()
}
