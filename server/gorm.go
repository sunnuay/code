package main

import (
	"gorm.io/datatypes"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"
)

var DB *gorm.DB

type User struct {
	ID       int            `gorm:"primaryKey" json:"id"`
	Username string         `gorm:"not null;unique" json:"username"`
	Settings datatypes.JSON `gorm:"not null" json:"settings"`
}

func InitDB(dsn string) error {
	var err error
	DB, err = gorm.Open(postgres.Open(dsn), &gorm.Config{})
	if err != nil {
		return err
	}
	return nil
}

func GetAllUsers() ([]User, error) {
	var users []User
	result := DB.Find(&users)
	return users, result.Error
}

func CreateUser(user *User) error {
	return DB.Create(user).Error
}
