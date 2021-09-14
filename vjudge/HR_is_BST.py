


def check_binary_search_tree_(root):
     def determineBST(root, left, right):
        
            if (root == None):
                return 1

            if ((left != None) and (root.data < left)):
                return 0

            if ((right != None) and (root.data > right)):
                return 0

            return (determineBST(root.left, left, root.data) and (determineBST(root.right, root.data, right)))

     return determineBST(root, None, None)


