import matplotlib.pyplot as plt 
  
# DP
y1 = [3.48, 4.037, 4.346 , 4.603, 4.663] 
x1 = [20,100,200,300,400] 
# plotting the line 1 points  
plt.plot(x1, y1, label = "MCDS",color='#0d3b84', 
linewidth = 1,marker='s', 
markerfacecolor='blue', markersize=4) 
  
#DCACDS 
x2 = x1
y2 = [3.45, 4.084, 4.4556, 4.8137, 4.8945] 
# plotting the line 2 points  
plt.plot(x2, y2, label = "Distributed CACDS", color='#1e6ded', 
linewidth = 1,marker='s', 
markerfacecolor='white', markersize=4) 

#Combained 
x3 = x1
y3 = [3.43, 3.93, 4.22 , 4.54, 4.555] 
# plotting the line 2 points  
plt.plot(x3, y3, label = "Combined", color='#1b4439', 
linewidth = 1,marker='s', 
markerfacecolor='#1b4439', markersize=4)   
  
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
