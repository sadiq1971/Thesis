import matplotlib.pyplot as plt 
plt.figure(figsize=(4.5, 3))  
# MCDS
y1 = [6.292, 6.643, 6.7, 7.15, 7.156, 7.030, 6.9566, 6.965] 
x1 = [50,100,150,200,250,300,350,400] 
# plotting the line 1 points  
plt.plot(x1, y1, label = "MCDS",color='#0d3b84', 
linewidth = 1,marker='s', 
markerfacecolor='blue', markersize=4)
  
#CACDS 
x2 = x1
y2 = [6.34, 6.643, 6.71, 7.152, 7.157, 7.030, 6.96, 6.96] 
# plotting the line 2 points  
plt.plot(x2, y2, label = "Centralized CACDS", color='#1e6ded', 
linewidth = 1,marker='s', 
markerfacecolor='white', markersize=4) 
axes = plt.gca()
# axes.set_ylim([2.5,4.0])  
  
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
