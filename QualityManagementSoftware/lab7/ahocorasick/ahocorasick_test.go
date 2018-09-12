package ahocorasick

import (
	"math/rand"
	"testing"
)

var dictionary = make([]string, 0)
var str string

func init() {
	rand.Seed(42)

	for i := 0; i < 200000; i++ {
		dictionary = append(dictionary, randWord(2, 6))
	}

	str = randWord(5000, 10000)
}

func BenchmarkOfw(b *testing.B) {

	ac := NewMatcher()
	ac.Build([]string{"foo", "bar", "baz"})

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		ac.Match("fooasldkjflaksjbarsdfasdfbazasdfdf")
	}
	b.ReportAllocs()
}

func BenchmarkHard(b *testing.B) {
	ac := NewMatcher()
	ac.Build(dictionary)

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		ac.Match(str)
	}
	b.ReportAllocs()
}

func randWord(m, n int) string {
	num := rand.Intn(n-m) + m
	var s string
	a := 'a'

	for i := 0; i < num; i++ {
		c := a + rune(rand.Intn(26))
		s = s + string(c)
	}

	return s
}
