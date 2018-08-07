package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	const MAX_NODE = 10
	const MAX_PACK = 10

	var timeTracket [MAX_NODE][MAX_PACK]float64
	var isForwardNode [MAX_NODE][MAX_PACK]bool
	var dropedPacket [MAX_PACK]int
	var forwardedPacket [MAX_PACK]int

	//initialize with -1
	for i := range timeTracket {
		for j := range timeTracket[i] {
			timeTracket[i][j] = -1
			isForwardNode[i][j] = false
			dropedPacket[j] = 0
			forwardedPacket[j] = 0
			//fmt.Println(timeTracket[i][j])
		}
	}

	fmt.Println("Welcome to the analyser")

	file, err := os.Open("wireless-flooding.tr")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanWords)

	totalDropPacket := 0
	totalForwardedPacket := 0

	for scanner.Scan() {
		words := scanner.Text()
		switch words {
		case "s":
			line := make(map[string]string)
			line["0"] = words
			for {
				scanner.Scan()
				temp := scanner.Text()
				if temp == "-Iv" {
					break
				}
				scanner.Scan()
				line[temp] = scanner.Text()
			}
			scanner.Scan()
			break

		case "f":
			totalForwardedPacket++
			line := make(map[string]string)
			line["0"] = words
			for {
				scanner.Scan()
				temp := scanner.Text()
				if temp == "-Iv" {
					//fmt.Println("t == ", line["-t"])
					//fmt.Println("Node Id == ", line["-Ni"])
					//fmt.Println("Network Layer == ", line["-Nl"])
					node, _ := strconv.ParseInt(line["-Ni"], 10, 64)
					packet, _ := strconv.ParseInt(line["-Ii"], 10, 64)

					isForwardNode[node][packet] = true
					forwardedPacket[packet]++

					break
				}
				scanner.Scan()
				line[temp] = scanner.Text()
			}
			scanner.Scan()
			break
		case "d":
			totalDropPacket++
			line := make(map[string]string)
			line["0"] = words
			for {
				scanner.Scan()
				temp := scanner.Text()
				if temp == "-Iv" {
					//fmt.Println("t == ", line["-t"])
					//fmt.Println("Node Id == ", line["-Ni"])
					//fmt.Println("Network Layer == ", line["-Nl"])
					packet, _ := strconv.ParseInt(line["-Ii"], 10, 64)
					dropedPacket[packet]++
					break
				}
				scanner.Scan()
				line[temp] = scanner.Text()
			}
			scanner.Scan()
			break
		case "r":
			line := make(map[string]string)
			line["0"] = words
			for {
				scanner.Scan()
				temp := scanner.Text()
				if temp == "-Iv" {
					//fmt.Println("t == ", line["-t"])
					//fmt.Println("Node Id == ", line["-Ni"])
					//fmt.Println("Network Layer == ", line["-Nl"])

					node, _ := strconv.ParseInt(line["-Ni"], 10, 64)
					packet, _ := strconv.ParseInt(line["-Ii"], 10, 64)

					if line["-Nl"] == "RTR" && timeTracket[node][packet] == -1 {
						//fmt.Println("Comes")
						timeTracket[node][packet], _ = strconv.ParseFloat(line["-t"], 64)
					}

					break
				}
				scanner.Scan()
				line[temp] = scanner.Text()
			}

			scanner.Scan()
			break
		}
	}

	//fmt.Println(l2)
	fmt.Println("Total droped packet", totalDropPacket)
	fmt.Println("Total forwarded packet", totalForwardedPacket+3)

	for i := 0; i < MAX_PACK; i++ {
		min := 100000.0
		max := -100000.0
		minNode := -1
		maxNode := -1

		for j := 0; j < MAX_NODE; j++ {
			if timeTracket[j][i] == -1 {
				continue
			}
			if timeTracket[j][i] < min {
				min = timeTracket[j][i]
				minNode = j
			}
			if timeTracket[j][i] > max {
				max = timeTracket[j][i]
				maxNode = j
			}
		}
		fmt.Println()
		if minNode != -1 && maxNode != -1 {
			fmt.Println("For packet id : ", i)
			fmt.Println("Delay = ", max-min)
			fmt.Println("Starting node: ", minNode, " End node: ", maxNode)
			fmt.Println("Total Dropped: ", dropedPacket[i])
			fmt.Println("Total Forwarded: ", forwardedPacket[i]+1)
			fmt.Print("Received by: ")
			for k := 0; k < MAX_NODE; k++ {
				if timeTracket[k][i] != -1 {
					fmt.Print(k, " ")
				}
			}
			fmt.Println()

		}

	}

}
