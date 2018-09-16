package main_test

import (
	"ahocorasick/ahocorasick"
	"reflect"
	"testing"
)

func TestSimple(t *testing.T) {
	UI()

	ac := ahocorasick.NewMatcher()

	dictionary := []string{"0", "1", "11"}
	ac.Build(dictionary)

	res := ac.Match("010")
	exp := []int{0, 1}

	if !reflect.DeepEqual(res, exp) {
		t.Errorf("Got: %d, want: %d.", res, exp)
	}
}
