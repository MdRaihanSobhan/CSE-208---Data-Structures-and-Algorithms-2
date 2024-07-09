import java.util.Vector;

public class GraphFibonacci {
    public Vector<Node> vertices;
    public Vector<Edge> edges;
    public int n;
    public int e;
    public int source;
    public int destination;
    public FibHeap fibHeap;

    public GraphFibonacci(Vector<Node> vertices, Vector<Edge> edges, int n, int e, int source, int destination, FibHeap fibHeap) {
        this.vertices = vertices;
        this.edges = edges;
        this.n = n;
        this.e = e;
        this.source = source;
        this.destination = destination;
        this.fibHeap = fibHeap;
    }
}
