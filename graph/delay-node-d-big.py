import matplotlib.pyplot as plt 
plt.figure(figsize=(4.5, 3))  
# DP
y1 = [3.823,4.037,4.2,4.346,4.541,4.644,4.667,4.662] 
x1 = [50,100,150,200,250,300,350,400] 
# plotting the line 1 points  
plt.plot(x1, y1, label = "DP",color='#0d3b84', 
linewidth = 1,marker='s', 
markerfacecolor='blue', markersize=4) 
  
#DCACDS 
x2 = x1
y2 = [3.813, 4.084, 4.3167,4.4556,4.6926,4.78,4.80,4.894] 
# plotting the line 2 points  
plt.plot(x2, y2, label = "Distributed CACDS", color='#1e6ded', 
linewidth = 1,marker='s', 
markerfacecolor='white', markersize=4) 

#Combained 
x3 = x1
y3 = [3.753,3.93,4.127,4.22,4.43,4.54,4.589,4.555] 
# plotting the line 2 points  
plt.plot(x3, y3, label = "HDCACDS", color='#1b4439', 
linewidth = 1,marker='v', 
markerfacecolor='white', markersize=6)   
  
# naming the x axis 
plt.xlabel('Number of nodes') 
# naming the y axis 
plt.ylabel('Delay (milisecond)') 
# giving a title to my graph 
plt.title('Transmission Range 250') 
  
# show a legend on the plot 
plt.legend() 
  
# function to show the plot 
plt.show() 
