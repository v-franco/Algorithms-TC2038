
        
def topView(root):

    nodesByDist={}
    output=""

    def top(root, nodesByDist, level, hDist):
        
        if (root == None):
            return None
            
        if (hDist not in nodesByDist) or (nodesByDist[hDist][1] > level):
            nodesByDist.update({hDist:[root.info, level]})

        top(root.left, nodesByDist, level+1, hDist-1)
        top(root.right, nodesByDist, level+1, hDist+1)
           
    top(root, nodesByDist, 0, 0)
        
    for key in sorted(nodesByDist.keys()):

        output+=(str(nodesByDist[key][0]))+" "

    print (output)
            
