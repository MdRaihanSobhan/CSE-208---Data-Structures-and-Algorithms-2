public class FibHeap {
    private Node[] rootListByRank = new Node[20000];
    private Node minRoot;
    private int numberOfNodes;

    public FibHeap() {
        this.minRoot= null;
        this.numberOfNodes=0;
    }

    public FibHeap(Node minRoot) {
        this.minRoot = minRoot;
        this.minRoot.leftSibling=null;
        this.minRoot.rightSibling=null;
        this.minRoot.parent=null;
        this.minRoot.children=null;
        this.minRoot.rank=0;
        this.numberOfNodes=0;
    }

    boolean isNull(){
        if(this.minRoot==null){
            return true;
        }
        else{
            return false;
        }
    }

    boolean insert(Node node){
        if(node==null){
            return false;
        }

        if(this.minRoot==null){
            minRoot=node;
        }
        else{
            this.minRoot.addSibling(node); // adding the new vertex next to the min pointer
            if(node.key<this.minRoot.key){
                this.minRoot= node;
            }
        }
        this.numberOfNodes++;
        return true;
    }

    private boolean fibLink(Node rootNode){
        if(rootListByRank[rootNode.rank]==null){
            rootListByRank[rootNode.rank]= rootNode;
            return false;
        }
        else {
            Node tempNode = rootListByRank[rootNode.rank];
            rootListByRank[rootNode.rank]= null;
            if(rootNode.key< tempNode.key || rootNode == this.minRoot){
                tempNode.removeNode();
                rootNode.addChild(tempNode);
                if(rootListByRank[rootNode.rank]!=null){
                    fibLink(rootNode);
                }
                else{
                    rootListByRank[rootNode.rank]= rootNode;
                }
            }
            else{
                rootNode.removeNode();
                tempNode.addChild(rootNode);
                if(rootListByRank[tempNode.rank]!=null){
                    fibLink(tempNode);
                }
                else{
                    rootListByRank[tempNode.rank]=tempNode;
                }
            }
            return true;
        }
    }

    public Node getMinRoot() {
        return minRoot;
    }

    public void decreaseKey(double decreasedWeight, Node node){
        node.key= decreasedWeight;
        if(node.parent!=null){
            node.removeNode();
            this.minRoot.addSibling(node);
        }
        if(node.key< this.minRoot.key){
            this.minRoot= node;
        }
    }

    public Node extractMin(){

        Node tempNode = new Node();
        Node nextTempNode= null;
        if(this.minRoot.children!=null) {
            tempNode = this.minRoot.children.leftMostSibling();
            // adding the children of min to rootlist
            while (tempNode != null) {
                nextTempNode = tempNode.rightSibling;
                tempNode.removeNode();
                this.minRoot.addSibling(tempNode);
                tempNode = nextTempNode;
            }
        }


        tempNode= this.minRoot.leftMostSibling();

        // extracting minroot and set it to any sibling if there is any
        if(tempNode==this.minRoot){
            if(this.minRoot.rightSibling!=null){
                tempNode= this.minRoot.rightSibling;
            }
            else{
                // empty heap , minroot is leftmost and right sibling is null
                Node extracted = this.minRoot;
                this.minRoot.removeNode();
                this.minRoot=null;
                return extracted;
            }
        }

        Node extracted = this.minRoot;
        this.minRoot.removeNode();
        this.minRoot= tempNode;


        // updating rootlist

        for(int i=0; i<20000; i++){
            rootListByRank[i]=null;
        }

        while (tempNode!=null){
            if(tempNode.key< this.minRoot.key){
                this.minRoot=tempNode;
            }
            nextTempNode= tempNode.rightSibling;
            fibLink(tempNode);
            tempNode= nextTempNode;
        }

        return extracted;
    }
}
