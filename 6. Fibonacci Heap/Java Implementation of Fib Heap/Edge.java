public class Edge {
    public Node head;
    public Node tail;
    public double weight;
    public double decreasedWeight;

    public Edge(Node tail, Node head, double weight) {
        this.head = head;
        this.tail = tail;
        this.weight = weight;
    }
}
