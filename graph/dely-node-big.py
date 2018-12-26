import matplotlib.pyplot as plt 
plt.figure(figsize=(4.5, 3))  
# MCDS
y1 = [3.193, 3.213,3.23, 3.38, 3.38,3.35,3.37,3.33] 
x1 = [50,100,150,200,250,300,350,400] 
# plotting the line 1 points  
plt.plot(x1, y1, label = "MCDS",color='#0d3b84', 
linewidth = 1,marker='s', 
markerfacecolor='blue', markersize=4)
  
#CACDS 
x2 = x1
y2 = [3.112,3.106,3.09,3.117, 3.21, 3.16,3.16, 3.15] 
# plotting the line 2 points  
plt.plot(x2, y2, label = "Centralized CACDS", color='#1e6ded', 
linewidth = 1,marker='s', 
markerfacecolor='white', markersize=4) 
axes = plt.gca()
axes.set_ylim([2.5,4.0])  
  
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
