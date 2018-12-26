import matplotlib.pyplot as plt   

plt.figure(figsize=(4, 5)) 

# MCDS
y1 = [4.88,6.446,6.938,8.297,11.12] 
x1 = [275,250,225,200,175] 
# plotting the line 1 points  
plt.plot(x1, y1, label = "MCDS",color='#0d3b84', 
linewidth = 1,marker='s', 
markerfacecolor='blue', markersize=4) 
  
#CACDS 
x2 = x1
y2 = [4.9, 6.5, 6.95, 8.3, 11.2] 
# plotting the line 2 points  
plt.plot(x2, y2, label = "Centralized CACDS", color='#1e6ded', 
linewidth = 1,marker='s', 
markerfacecolor='white', markersize=4) 
axes = plt.gca()
# axes.set_ylim([2.7,3.7])  
  
# naming the x axis 
plt.xlabel('Transmission Range(m)') 
# naming the y axis 
plt.ylabel('Average forwarding nodes') 
# giving a title to my graph 
plt.title('Number of nodes 40') 
  
# show a legend on the plot 
plt.legend() 

# function to show the plot 

fig = plt.gcf()

plt.show()