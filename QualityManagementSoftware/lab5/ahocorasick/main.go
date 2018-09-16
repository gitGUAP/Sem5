package main

import (
	"ahocorasick/ahocorasick"
	"strings"

	"github.com/lxn/walk"
	. "github.com/lxn/walk/declarative"
)

func UI() {
	var strTE,substrTE,outTE *walk.TextEdit

	MainWindow{
		Title:   "Aho",
		MinSize: Size{600, 400},
		Layout:  VBox{},
		Children: []Widget{
			HSplitter{
				Children: []Widget{
					TextEdit{AssignTo: &strTE},
					TextEdit{AssignTo: &substrTE},
					TextEdit{AssignTo: &outTE, ReadOnly: true},
				},
			},
			PushButton{
				Text: "Run",
				OnClicked: func() {
					substrSlice := strings.Split(substrTE.Text(), ",")

					// Trim
					for i,val:= range substrSlice {
						substrSlice[i] = strings.TrimSpace(val)
					}

					// Filter
					temp := []string{}
					for _,value := range substrSlice {
						if len(value) > 0 {
							temp = append(temp, value)
						}
					}
					substrSlice = temp

					// Alg
					ac := ahocorasick.NewMatcher()
					ac.Build(substrSlice)
					res := ac.Match(strTE.Text())

					// Slice of index to Map
					out := ""

					for _, i := range res {
						out += substrSlice[i] + "\r\n"
					}

					outTE.SetText(out)
				},
			},
		},
	}.Run()

}

func main() {
	UI()
}
