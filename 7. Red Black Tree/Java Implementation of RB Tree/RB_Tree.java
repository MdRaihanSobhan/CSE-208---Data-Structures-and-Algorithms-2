public class RB_Tree implements RB_ADT {

    private LinkNode rootNode;
    private LinkNode NIL;

    public LinkNode getRootNode() {
        return rootNode;
    }

    public RB_Tree() {
        NIL = new LinkNode();
        NIL.setColor(0); // leaves are black
        rootNode= new LinkNode();
        rootNode=NIL; // root is black
    }

    public LinkNode getMin(LinkNode linkNode){
        while (linkNode.getLeftNode()!=NIL){
            linkNode=linkNode.getLeftNode();
        }
        return linkNode;
    }

    public LinkNode getMax(LinkNode linkNode){
        while (linkNode.getRightNode()!=NIL){
            linkNode=linkNode.getRightNode();
        }
        return linkNode;
    }


    public void leftRotate(LinkNode x){
        LinkNode y= x.getRightNode();
        x.setRightNode(y.getLeftNode());
        if(y.getLeftNode()!=NIL){
            y.getLeftNode().setParent(x);
        }
        y.setParent(x.getParent());

        if(x.getParent()==null){
            this.rootNode=y;
        }
        else if(x==x.getParent().getLeftNode()){
            x.getParent().setLeftNode(y);
        }
        else{
            x.getParent().setRightNode(y);
        }

        y.setLeftNode(x);
        x.setParent(y);

        y.setSize(x.getSize());
        x.setSize(x.getLeftNode().getSize()+ x.getRightNode().getSize()+1);

    }

    public void rightRotate(LinkNode x){
        LinkNode y= x.getLeftNode();
        x.setLeftNode(y.getRightNode());
        if(y.getRightNode()!=NIL){
            y.getRightNode().setParent(x);
        }
        y.setParent(x.getParent());

        if(x.getParent()==null){
            this.rootNode=y;
        }
        else if(x==x.getParent().getRightNode()){
            x.getParent().setRightNode(y);
        }
        else{
            x.getParent().setLeftNode(y);
        }
        y.setRightNode(x);
        x.setParent(y);

        y.setSize(x.getSize());
        x.setSize(x.getLeftNode().getSize()+ x.getRightNode().getSize()+1);
    }

    public LinkNode insertHelper(int data){
        LinkNode linkNode= new LinkNode(data);
        linkNode.setColor(1); // initially red
        linkNode.setLeftNode(NIL);
        linkNode.setRightNode(NIL);


        LinkNode y = null;
        LinkNode x = this.rootNode;

        while (x != NIL) {
            y = x;

            y.setSize(y.getSize()+1);

            if (linkNode.getData() < x.getData()) {
                x = x.getLeftNode();
            }
            else if (linkNode.getData()>x.getData()) {
                x = x.getRightNode();
            }
            else {
                LinkNode tempNode= x;

                while (tempNode!=this.rootNode){
                    tempNode.setSize(tempNode.getSize()-1);
                    tempNode= tempNode.getParent();
                }
                this.rootNode.setSize(this.rootNode.getSize()-1);

                return null;
            }
        }

        linkNode.setParent(y);
        if (y == null) {
            this.rootNode = linkNode;
        } else if (linkNode.getData() < y.getData()) {
            y.setLeftNode(linkNode);
        } else {
            y.setRightNode(linkNode);
        }

        linkNode.setSize(1);
        linkNode.setLeftNode(NIL);
        linkNode.setRightNode(NIL);
        linkNode.setColor(1);

        return linkNode;
    }

    @Override
    public int RB_Insert(int data){
        LinkNode linkNode= insertHelper(data);

        if(linkNode==null){
            return 0;
        }

        if (linkNode.getParent() == null){
            linkNode.setColor(0);
            return 1;
        }

        if (linkNode.getParent().getParent() == null) {
            return 1;
        }

        FixUp_Insert(linkNode);
        return 1;
    }


    private void FixUp_Insert(LinkNode linkNode){
        LinkNode uncle;

        while (linkNode.getParent().getColor()==1){
            // or baba jodi or dadar left child hoy
            if(linkNode.getParent()==linkNode.getParent().getParent().getLeftNode()){
                // or chacha tahole or dadar right child
                uncle= linkNode.getParent().getParent().getRightNode();
                // oy o lal, or bap o lal, or chacha o lal
                if(uncle.getColor()==1){
                    // dadar shathe bap chachar color swap kore dei
                    // dada kalo eta sure
                    uncle.setColor(0);
                    linkNode.getParent().setColor(0);
                    linkNode.getParent().getParent().setColor(1);
                    linkNode= linkNode.getParent().getParent();
                }
                else{
                    // zigzag to zigzig by first rotation
                    if(linkNode==linkNode.getParent().getRightNode()){
                        linkNode=linkNode.getParent();
                        leftRotate(linkNode);
                    }
                    // zigzig
                    linkNode.getParent().setColor(0);
                    linkNode.getParent().getParent().setColor(1);
                    rightRotate(linkNode.getParent().getParent());
                }
            }
            // or baba jodi or dadar right child hoy
            else {
                // tahole or chacha hobe or dadar left child
                uncle= linkNode.getParent().getParent().getLeftNode();
                // oy o lal, or bap o lal, or chacha o lal
                if(uncle.getColor()==1){
                    // dadar shathe bap chachar color swap kore dei
                    // dada kalo eta sure
                    uncle.setColor(0);
                    linkNode.getParent().setColor(0);
                    linkNode.getParent().getParent().setColor(1);
                    linkNode= linkNode.getParent().getParent(); // upore lal lal mile jaite pare
                }
                // oy lal, or bap lal, kintu chacha kalo
                else{
                    // zigzag
                    if(linkNode==linkNode.getParent().getLeftNode()){
                        linkNode=linkNode.getParent();
                        rightRotate(linkNode);
                    }
                    // zigzig
                    linkNode.getParent().setColor(0);
                    linkNode.getParent().getParent().setColor(1);
                    leftRotate(linkNode.getParent().getParent());
                }
            }

            if(linkNode==this.rootNode) break;
        }
        this.rootNode.setColor(0);
    }

    private void transplant(LinkNode x, LinkNode y){
        if(x.getParent()==null){
            this.rootNode=y;
        }
        else if(x==x.getParent().getLeftNode()){
            x.getParent().setLeftNode(y);
        }
        else if(x==x.getParent().getRightNode()){
            x.getParent().setRightNode(y);
        }
        y.setParent(x.getParent());
    }

    private int deleteHelper(LinkNode linkNode, int data){
        LinkNode x, y;
        LinkNode z= NIL;
        while (linkNode!=NIL){
            if(linkNode.getData()==data){
                z=linkNode;
            }
            if(linkNode.getData()<=data){
                linkNode= linkNode.getRightNode();
            }
            else if(linkNode.getData()>data) {
                linkNode= linkNode.getLeftNode();
            }
        }

        if(z==NIL){
            return 0; // priority not found
        }

        if(z!=this.rootNode){
            LinkNode tempNode = z.getParent();
            while (tempNode!=this.rootNode){
                tempNode.setSize(tempNode.getSize()-1);
                tempNode= tempNode.getParent();
            }
            this.rootNode.setSize(this.rootNode.getSize()-1);
        }

        y=z;
        int yMainColor = y.getColor();
        if(z.getLeftNode()==NIL){
            x= z.getRightNode();
            transplant(z, z.getRightNode());
        }
        else if(z.getRightNode()==NIL){
            x=z.getLeftNode();
            transplant(z,z.getLeftNode());
        }
        else{
            y= getMin(z.getRightNode());
            yMainColor= y.getColor();
            x=y.getRightNode();
            if(y.getParent()==z){
                x.setParent(y);
            }
            else{
                transplant(y, y.getRightNode());
                y.setRightNode(z.getRightNode());
                y.getRightNode().setParent(y);

                LinkNode tempNode= x.getParent();
                while (tempNode!=y){
                    tempNode.setSize(tempNode.getSize()-1);
                    tempNode= tempNode.getParent();
                }
                y.setSize(y.getLeftNode().getSize()+1);

            }
            transplant(z,y);
            y.setLeftNode(z.getLeftNode());
            y.getLeftNode().setParent(y);
            y.setColor(z.getColor());

            y.setSize(y.getLeftNode().getSize()+ y.getRightNode().getSize()+ 1 );
        }

        if(yMainColor==0){
            FixUp_Delete(x); // If I delete a black node
        }

        return 1;

    }

    private void FixUp_Delete(LinkNode deletedNode){
        LinkNode sibling;
        while (deletedNode!=this.rootNode && deletedNode.getColor()==0){
            if(deletedNode==deletedNode.getParent().getLeftNode()){
                sibling=deletedNode.getParent().getRightNode();
                if(sibling.getColor()==1){
                    sibling.setColor(0);
                    deletedNode.getParent().setColor(1);
                    leftRotate(deletedNode.getParent());
                    sibling = deletedNode.getParent().getRightNode();
                }

                if(sibling.getLeftNode().getColor()==0 && sibling.getRightNode().getColor()==0){
                    sibling.setColor(1);
                    deletedNode = deletedNode.getParent();
                }
                else{
                    if(sibling.getRightNode().getColor()==0){
                        sibling.getLeftNode().setColor(0);
                        sibling.setColor(1);
                        rightRotate(sibling);
                        sibling = deletedNode.getParent().getRightNode();;
                    }

                    sibling.setColor(deletedNode.getParent().getColor());
                    deletedNode.getParent().setColor(0);
                    sibling.getRightNode().setColor(0);
                    leftRotate(deletedNode.getParent());
                    deletedNode = this.rootNode;
                }
            }
            else{
                // left->right, right->left
                sibling = deletedNode.getParent().getLeftNode();
                if(sibling.getColor()==1){
                    sibling.setColor(0);
                    deletedNode.getParent().setColor(1);
                    rightRotate(deletedNode.getParent());
                    sibling = deletedNode.getParent().getLeftNode();
                }

                if(sibling.getLeftNode().getColor()==0 && sibling.getRightNode().getColor()==0){
                    sibling.setColor(1);
                    deletedNode = deletedNode.getParent();
                }
                else{
                    if(sibling.getLeftNode().getColor()==0){
                        sibling.getRightNode().setColor(0);
                        sibling.setColor(1);
                        leftRotate(sibling);
                        sibling = deletedNode.getParent().getLeftNode();
                    }

                    sibling.setColor(deletedNode.getParent().getColor());
                    deletedNode.getParent().setColor(0);
                    sibling.getLeftNode().setColor(0);
                    rightRotate(deletedNode.getParent());
                    deletedNode= this.rootNode;
                }
            }

        }
        deletedNode.setColor(0);
    }
    @Override
    public int RB_Delete(int data) {
        return deleteHelper(this.rootNode, data);
    }

    private Boolean findHelper(int data, LinkNode node) {
        Boolean flag= false;
        if(node.getData()==data)
            flag=true;
        else if(data< node.getData() && node.getLeftNode()!=null && node.getLeftNode()!=NIL ){
            flag=findHelper(data,node.getLeftNode());
        }
        else if(data> node.getData() && node.getRightNode()!=null && node.getRightNode()!=NIL){
            flag=findHelper(data,node.getRightNode());
        }
        return flag;
    }

    @Override
    public int RB_Find(int data) {
        if(findHelper(data,this.rootNode)==true) return 1;
        else return 0;
    }

    public int priorityCount(LinkNode linkNode, int low, int high)
    {
        if(linkNode == null || linkNode== NIL)
            return 0;

        if(linkNode.getData() >= low && linkNode.getData() <= high)
            return 1 + this.priorityCount(linkNode.getLeftNode(), low, high)+
                    this.priorityCount(linkNode.getRightNode(), low, high);

        else if(linkNode.getData() < low)
            return this.priorityCount(linkNode.getRightNode(), low, high);

        else
            return this.priorityCount(linkNode.getLeftNode(), low, high);
    }

    public int countLowers(LinkNode linkNode, int data){
        int cnt=0;
        LinkNode tempNode = linkNode;
        while (tempNode!=NIL){
            if(tempNode.getData()>data){
                tempNode= tempNode.getLeftNode();
            }
            else if(tempNode.getData()<data){
                cnt+= (tempNode.getLeftNode().getSize()+1) ;
                tempNode= tempNode.getRightNode();
            }
            else{
                return cnt+ tempNode.getLeftNode().getSize();
            }
        }
        return cnt ;
    }

}
