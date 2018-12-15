package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	const MAX_NODE = 100
	const MAX_PACK = 100000

	var timeTracket [MAX_NODE][MAX_PACK]float64
	var isForwardNode [MAX_NODE][MAX_PACK]bool
	var dropedPacket [MAX_PACK]int
	var forwardedPacket [MAX_PACK]int
	var validPackate = 0
	averageCollision := 0
	reachability := 0

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

	// fmt.Println("Welcome to the analyser")

	file, err := os.Open("../wireless-flooding.tr")
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
					node, _ := strconv.ParseInt(line["-Ni"], 10, 64)
					packet, _ := strconv.ParseInt(line["-Ii"], 10, 64)
					layer := line["-Nl"]
					if layer == "RTR" {
						isForwardNode[node][packet] = true
						forwardedPacket[packet]++
						totalForwardedPacket++
					}

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
					col := line["-Nw"]
					if col == "COL" {
						averageCollision++
					}
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

	var averageDelay = 0.0
	var totalDelay = 0.0
	successfullForwarding := 0

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

		if minNode != -1 && maxNode != -1 {
			// fmt.Println()
			validPackate++
			// fmt.Println("For packet id : ", i)
			// fmt.Println("Delay = ", max-min)
			totalDelay += max - min
			// fmt.Println("Starting node: ", minNode, " End node: ", maxNode)
			// fmt.Println("Total Dropped: ", dropedPacket[i])
			// fmt.Println("Total Forwarded: ", forwardedPacket[i])
			// fmt.Print("Received by: ")

			totalReceived := 0
			for k := 0; k < MAX_NODE; k++ {
				if timeTracket[k][i] != -1 {
					// fmt.Print(k, " ")
					totalReceived++
					reachability++
				}
			}
			if totalReceived == MAX_NODE {
				averageDelay += max - min
				successfullForwarding++
			}
			// fmt.Println()

		}

	}

	// fmt.Println("Total droped packet", totalDropPacket)
	// fmt.Println("Total forwarded packet", totalForwardedPacket)
	var averageForwarding = float64(totalForwardedPacket) / float64(validPackate)
	// var averageDropped = float64(totalDropPacket) / float64(validPackate)

	// fmt.Println("Average DroppedPacket: ", averageDropped)
	// fmt.Println("Average Delay (For succ pkt only): ", float64(averageDelay)/float64(successfullForwarding))
	fmt.Println("Average_Delay: ",
		float64(totalDelay)/float64(validPackate))
	fmt.Println("Reachability_in_percentage: ",
		float64(reachability)/(float64(validPackate)*float64(MAX_NODE)))
	// fmt.Println("Packet received by all nodes: ", successfullForwarding)
	fmt.Println("Average_Forwarding:", averageForwarding)
	fmt.Println("Average_Collision: ",
		float64(averageCollision)/float64(validPackate))

}
