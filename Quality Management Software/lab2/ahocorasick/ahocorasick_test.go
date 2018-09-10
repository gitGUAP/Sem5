package ahocorasick

import (
	"io/ioutil"
	"reflect"
	"strconv"
	"strings"
	"testing"
)

func TestSimple(t *testing.T) {
	ac := NewMatcher()

	dictionary := []string{"0", "1", "11"}
	ac.Build(dictionary)

	res := ac.Match("010")
	exp := []int{0, 1}

	if !reflect.DeepEqual(res, exp) {
		t.Errorf("Got: %d, want: %d.", res, exp)
	}
}

func TestHard(t *testing.T) {
	ac := NewMatcher()

	// Create list of number
	dictionary := make([]string, 10e5)
	for i := range dictionary {
		dictionary[i] = strconv.Itoa(i)
	}

	ac.Build(dictionary)

	// Concat dictionary
	match := strings.Join(dictionary, "")

	l := ac.GetMatchResultSize(match)

	if l != len(dictionary) {
		t.Errorf("Length not match: %d and %d", l, len(dictionary))
	}
}

func TestIntersection(t *testing.T) {
	ac := NewMatcher()

	dictionary := []string{"hello", "world", "привет", "golang", "c++", "love", "not love"}

	ac.Build(dictionary)

	l := ac.GetMatchResultSize("hello世界, hello, i love golang!!!")
	exp := 3
	if l != exp {
		t.Errorf("Length not match: %d and %d", l, exp)
	}
}

func TestFile(t *testing.T) {
	ac := NewMatcher()

	dictionary := []string{"hello", "world", "привет", "golang", "c++", "love", "not love"}

	ac.Build(dictionary)

	dat, err := ioutil.ReadFile("./input.txt")
	if err != nil {
		panic(err)
	}

	l := ac.GetMatchResultSize(string(dat))
	exp := 3
	if l != exp {
		t.Errorf("Length not match: %d and %d", l, exp)
	}
}
