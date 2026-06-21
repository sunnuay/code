package main

import (
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

func handleConn(conn net.Conn) {}

func handleHTTP(conn net.Conn) {}

func handleSocks(conn net.Conn) {}
