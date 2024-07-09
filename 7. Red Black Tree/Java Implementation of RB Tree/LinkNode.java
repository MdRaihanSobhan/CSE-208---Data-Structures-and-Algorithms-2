public class LinkNode {
    private int data;
    private LinkNode leftNode;
    private LinkNode rightNode;
    private LinkNode parent;
    private int color; // 0 for Black, 1 for Red
    private int size;

    public LinkNode() {
        leftNode=rightNode=parent=null;
    }

    public LinkNode(int data) {
        this.data = data;
        leftNode= rightNode= parent= null;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public int getData() {
        return data;
    }

    public void setData(int data) {
        this.data = data;
    }

    public LinkNode getLeftNode() {
        return leftNode;
    }

    public void setLeftNode(LinkNode leftNode) {
        this.leftNode = leftNode;
    }

    public LinkNode getRightNode() {
        return rightNode;
    }

    public void setRightNode(LinkNode rightNode) {
        this.rightNode = rightNode;
    }

    public LinkNode getParent() {
        return parent;
    }

    public void setParent(LinkNode parent) {
        this.parent = parent;
    }

    public int getColor() {
        return color;
    }

    public void setColor(int color) {
        this.color = color;
    }
}