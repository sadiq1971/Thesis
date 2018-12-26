import matplotlib.pyplot as plt 
plt.figure(figsize=(4, 5))  
# DP
y1 = [6.923,9.233,10.494,12.563,15.48] 
x1 = [275, 250, 225, 200, 175] 
# plotting the line 1 points  
plt.plot(x1, y1, label = "DP",color='#0d3b84', 
linewidth = 1,marker='s', 
markerfacecolor='blue', markersize=4) 
  
#DCACDS 
x2 = x1
y2 = [7.535,9.662,10.829,12.997,15.71] 
# plotting the line 2 points  
plt.plot(x2, y2, label = "Distributed CACDS", color='#1e6ded', 
linewidth = 1,marker='s', 
markerfacecolor='white', markersize=4) 

#Combained 
x3 = x1
y3 = [6.96,9.275,10.508,12.598,15.562] 
# plotting the line 2 points  
plt.plot(x3, y3, label = "HDCACDS", color='#1b4439', 
linewidth = 1,marker='v', 
markerfacecolor='white', markersize=6)   
  
# naming the x axis 
plt.xlabel('Transmission Range(m)') 
# naming the y axis 
plt.ylabel('Average forwarding nodes') 
# giving a title to my graph 
plt.title('Number of nodes 40') 
  
# show a legend on the plot 
plt.legend() 
  
# function to show the plot 
plt.show() 
