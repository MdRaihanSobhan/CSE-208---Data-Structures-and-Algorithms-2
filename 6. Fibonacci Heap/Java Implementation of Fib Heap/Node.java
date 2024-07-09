
import java.util.Vector;

public class Node {
    public Node parent;
    public Node leftSibling;
    public Node rightSibling;
    public Node children;
    public Node pred;


    public int data;
    public double key;
    public int rank;

    public States state;
    public Mark mark;

    public Vector<Edge> incomingEdges;
    public Vector<Edge> outgoingEdges;


    public Node() {
        this.parent= null;
        this.children= null;
        this.leftSibling= null;
        this.rightSibling=null;
        this.pred= null;
        this.rank= 0;
        this.state= States.unmarked;
        this.mark= Mark.white;
        this.incomingEdges= new Vector<Edge>();
        this.outgoingEdges= new Vector<Edge>();
    }

    public Node(int data, double key) {
        this.parent = null;
        this.leftSibling = null;
        this.rightSibling = null;
        this.children = null;
        this.pred = null;
        this.data = data;
        this.key = key;
        this.rank = 0;
        this.mark=Mark.white;
        this.state = States.unmarked;
        this.incomingEdges= new Vector<Edge>();
        this.outgoingEdges= new Vector<Edge>();
    }

    Node leftMostSibling(){
        if(this== null){
            return null;
        }
        Node temp = this;
        while (temp.leftSibling!=null){
            temp=temp.leftSibling;
        }
        return temp;
    }

    Node rightMostSibling(){
        if(this== null){
            return null;
        }
        Node temp = this;
        while (temp.rightSibling!=null){
            temp=temp.rightSibling;
        }
        return temp;
    }

    public void addIncomingEdge(Edge edge){
        this.incomingEdges.add(edge);
    }
    void addOutgoingEdge(Edge edge){
       this.outgoingEdges.add(edge);
    }

    boolean removeNode(){

        if(parent!=null){
            parent.rank--;
            if(leftSibling!=null){
                parent.children= leftSibling;
            }
            else if(rightSibling!=null){
                parent.children= rightSibling;
            }
            else{
                parent.children= null;
            }
        }

        if(leftSibling!=null){
            leftSibling.rightSibling= this.rightSibling;
        }
        if(rightSibling!=null){
            rightSibling.leftSibling= this.leftSibling;
        }
        this.leftSibling= null;
        this.rightSibling=null;
        this.parent=null;

        return true;
    }



    boolean addSibling (Node node){
        Node temp= this.rightMostSibling();
        if(temp==null){
            return false;   // This node doesn't exist;
        }
        temp.rightSibling= node;
        node.leftSibling= temp;
        node.rightSibling=null;
        node.parent=this.parent;
        if(parent!=null){
            parent.rank++;
        }
        return true;
    }

    boolean addChild (Node node){
        if(children!=null){
            children.addSibling(node);
        }
        else{
            children= node;
            node.parent= this;
            this.rank=1;
        }
        return true;
    }




}
