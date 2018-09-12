package main

import (
	"ahocorasick/ahocorasick"
	"github.com/buger/jsonparser"
	"github.com/gin-gonic/gin"
	"io/ioutil"
	"net/http"
	"strings"
)

type inp struct {
	str    string
	substr string
}

func main() {
	router := gin.Default()
	router.Static("/", "./")

	router.POST("/calc", func(c *gin.Context) {
		buf, err := ioutil.ReadAll(c.Request.Body)
		if err != nil {
			c.JSON(http.StatusInternalServerError, gin.H{
				"error": err,
			})
			return
		}

		str, _ := jsonparser.GetString(buf, "str")
		substr, _ := jsonparser.GetString(buf, "substr")
		substrSlice := strings.Split(substr, ",")

		// Trim
		for i, val := range substrSlice {
			substrSlice[i] = strings.TrimSpace(val)
		}

		// Filter
		temp := []string{}
		for _, value := range substrSlice {
			if len(value) > 0 {
				temp = append(temp, value)
			}
		}
		substrSlice = temp

		// Alg
		ac := ahocorasick.NewMatcher()
		ac.Build(substrSlice)
		res := ac.Match(str)

		// Slice of index to Map
		out := make(map[string]bool)
		for _, val := range substrSlice {
			out[val] = false
		}
		for _, i := range res {
			out[substrSlice[i]] = true
		}

		c.JSON(http.StatusOK, out)
	})

	router.Run(":8080")
}
