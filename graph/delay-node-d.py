import matplotlib.pyplot as plt 
  
# DP
y1 = [3.48,3.58,3.77,3.73,3.87,3.926,3.98] 
x1 = [20,30,40,50,60,70,80] 
# plotting the line 1 points  
plt.plot(x1, y1, label = "MCDS",color='#0d3b84', 
linewidth = 1,marker='s', 
markerfacecolor='blue', markersize=4) 
  
#DCACDS 
x2 = x1
y2 = [3.45,3.50,3.725,3.69,3.85,3.92,4.03] 
# plotting the line 2 points  
plt.plot(x2, y2, label = "Distributed CACDS", color='#1e6ded', 
linewidth = 1,marker='s', 
markerfacecolor='white', markersize=4) 

#Combained 
x3 = x1
y3 = [3.43,3.496,3.72,3.61,3.77,3.84,3.90] 
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
