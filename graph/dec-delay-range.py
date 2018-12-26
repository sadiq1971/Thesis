import matplotlib.pyplot as plt 
plt.figure(figsize=(4, 5))  
# DP
y1 = [3.23, 3.77, 3.99, 4.374, 5.04] 
x1 = [275, 250, 225, 200, 175] 
# plotting the line 1 points  
plt.plot(x1, y1, label = "DP",color='#0d3b84', 
linewidth = 1,marker='s', 
markerfacecolor='blue', markersize=4) 
  
#DCACDS 
x2 = x1
y2 = [3.20, 3.72, 3.96, 4.33, 4.99] 
# plotting the line 2 points  
plt.plot(x2, y2, label = "Distributed CACDS", color='#1e6ded', 
linewidth = 1,marker='s', 
markerfacecolor='white', markersize=4) 

#Combained 
x3 = x1
y3 = [3.135, 3.71, 3.91, 4.296, 4.968] 
# plotting the line 2 points  
plt.plot(x3, y3, label = "HDCACDS", color='#1b4439', 
linewidth = 1,marker='v', 
markerfacecolor='white', markersize=6)   
  
# naming the x axis 
plt.xlabel('Transmission Range(m)') 
# naming the y axis 
plt.ylabel('Delay (milisecond)') 
# giving a title to my graph 
plt.title('Number of nodes 40') 
  
# show a legend on the plot 
plt.legend() 
  
# function to show the plot 
plt.show() 
