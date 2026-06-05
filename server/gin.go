package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

func SetupRouter() *gin.Engine {
	r := gin.Default()
	r.GET("/grpc", testGrpc)
	r.GET("/users", getUsers)
	r.POST("/users", createUser)
	return r
}

// curl 127.0.0.1:8080/grpc?text=torch
func testGrpc(c *gin.Context) {
	result, err := GrpcClient(c.Query("text"))
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}

	c.JSON(http.StatusOK, gin.H{"data": result})
}

// curl 127.0.0.1:8080/users
func getUsers(c *gin.Context) {
	users, err := GetAllUsers()
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}

	c.JSON(http.StatusOK, gin.H{"data": users})
}

// curl -X POST 127.0.0.1:8080/users -d '{"username": "test", "settings": {}}'
func createUser(c *gin.Context) {
	var user User
	if err := c.ShouldBindJSON(&user); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	if err := CreateUser(&user); err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": err.Error()})
		return
	}

	c.JSON(http.StatusOK, gin.H{"data": user})
}
