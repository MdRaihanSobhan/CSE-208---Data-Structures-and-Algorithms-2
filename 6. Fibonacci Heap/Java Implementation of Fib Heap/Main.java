import java.util.Scanner;
import java.util.Vector;

public class Main {

    public static void main(String[] args) {
        Vector<Node> vertices = new Vector<Node>();
        Vector<Edge> edges = new Vector<Edge>();
        Scanner scanner = new Scanner(System.in);
        int n= scanner.nextInt();
        int e= scanner.nextInt();
        for(int i=0;i<n;i++){
            Node node= new Node( i, -1);
            vertices.add(node);
        }


        for(int i=0; i<e; i++){
            int h,t;
            double weight;
            t= scanner.nextInt();
            h=scanner.nextInt();
            weight=scanner.nextDouble();
            // System.out.println(tail+ " " + head + " " + weight );

            Edge edge = new Edge(vertices.get(t), vertices.get(h), weight);

            edge.tail.addOutgoingEdge(edge);
            edge.head.addIncomingEdge(edge);
            edges.add(edge);

            int temp = t;
            t= h;
            h= temp;

            Edge edge2 = new Edge(vertices.get(t), vertices.get(h), weight);

            edge2.tail.addOutgoingEdge(edge2);
            edge2.head.addIncomingEdge(edge2);
            edges.add(edge2);

        }
        int source, destination;
        source= scanner.nextInt();
        destination= scanner.nextInt();
        vertices.get(destination).key=0;
        vertices.get(destination).state= States.marked;

        FibHeap fibHeap = new FibHeap();
        fibHeap.insert(vertices.get(destination));


        do{
            Node node = fibHeap.extractMin();
            node.state= States.scanned;

            for(int i=0; i<node.incomingEdges.size(); i++){
                Edge newEdge = node.incomingEdges.get(i);
                Node headNewEdge= newEdge.tail;
                if(headNewEdge.state!=States.scanned){
                    if(headNewEdge.state==States.unmarked){
                        headNewEdge.state= States.marked;
                        headNewEdge.pred= node;
                        headNewEdge.key= node.key+ newEdge.weight;
                        fibHeap.insert(headNewEdge);
                    }
                    else if (headNewEdge.key> node.key+ newEdge.weight){
                        headNewEdge.pred= node;
                        fibHeap.decreaseKey(node.key+newEdge.weight, headNewEdge);
                    }
                }
            }
            if(node.data==vertices.get(source).data) break;
        }while (fibHeap.isNull()!=true);

        Node tempNode = vertices.get(source);
        if(tempNode.pred==null){
            System.out.println("No path exists");
            return;
        }

        int nodeCount=0;
        System.out.println("Shortest Path Cost : "+ vertices.get(source).key);

        while (tempNode!=null){
            System.out.print(tempNode.data);
            tempNode=tempNode.pred;
            if(tempNode!=null){
                System.out.print(" -> ");
            }
            nodeCount++;
        }
        System.out.println();

        System.out.println("Nodes visited "+ nodeCount);
    }
}
