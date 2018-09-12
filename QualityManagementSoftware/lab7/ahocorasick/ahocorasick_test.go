package ahocorasick

import (
	"math/rand"
	"strconv"
	"strings"
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

	l := ac.MatchSize(match)

	if l != len(dictionary) {
		t.Errorf("Length not match: %d and %d", l, len(dictionary))
	}
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
