import matplotlib.pyplot as plt 
plt.figure(figsize=(4.5, 3)) 
# DP
y1 = [9.5, 10.671, 11.418, 11.792, 12.934, 13.2567, 13.433, 13.655] 
x1 = [50,100,150,200,250,300,350,400] 
# plotting the line 1 points  
plt.plot(x1, y1, label = "DP",color='#0d3b84', 
linewidth = 1,marker='s', 
markerfacecolor='blue', markersize=4) 
  
#DCACDS 
x2 = x1
y2 = [10.3075, 12.083, 13.11, 13.594, 14.955, 15.237, 15.61, 15.84] 
# plotting the line 2 points  
plt.plot(x2, y2, label = "Distributed CACDS", color='#1e6ded', 
linewidth = 1,marker='s', 
markerfacecolor='white', markersize=4) 

#Combained 
x3 = x1
y3 = [9.646, 10.823, 11.66, 11.934, 13.012, 13.43, 13.6, 13.83] 
# plotting the line 2 points  
plt.plot(x3, y3, label = "HDCACDS", color='#1b4439', 
linewidth = 1,marker='v', 
markerfacecolor='white', markersize=6)   
  
# naming the x axis 
plt.xlabel('Number of nodes') 
# naming the y axis 
plt.ylabel('Average forwarding nodes')  
# giving a title to my graph 
plt.title('Transmission Range 250') 
  
# show a legend on the plot 
plt.legend() 
  
# function to show the plot 
plt.show() 
