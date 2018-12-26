import matplotlib.pyplot as plt   

plt.figure(figsize=(4.5, 3))

# MCDS
y1 = [3.078,3.16,3.21,3.193,3.14,3.21,3.21] 
x1 = [20,30,40,50,60,70,80] 
# plotting the line 1 points  
plt.plot(x1, y1, label = "MCDS",color='#0d3b84', 
linewidth = 1,marker='s', 
markerfacecolor='blue', markersize=4) 
  
#CACDS 
x2 = x1
y2 = [3.05,3.11,3.14,3.11,3.07,3.05,3.13] 
# plotting the line 2 points  
plt.plot(x2, y2, label = "Centralized CACDS", color='#1e6ded', 
linewidth = 1,marker='s', 
markerfacecolor='white', markersize=4) 
axes = plt.gca()
axes.set_ylim([2.7,3.7])  
  
# naming the x axis 
plt.xlabel('Number of nodes') 
# naming the y axis 
plt.ylabel('Delay (milisecond)') 
# giving a title to my graph 
plt.title('Transmission Range 250') 
  
# show a legend on the plot 
plt.legend() 

# function to show the plot 

fig = plt.gcf()

plt.show()
fig.savefig('cen_small_delay_node1.eps', format='eps', dpi=2000)