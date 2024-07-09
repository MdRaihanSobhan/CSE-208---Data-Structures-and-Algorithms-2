import java.util.Vector;

public class Matrices {
    private Vector<Vector<Integer>> vector= new Vector<Vector<Integer>>();
    private int bound;
    private int fixedRow;
    private int fixedColumn;
    private int level;
    private int position;
    private int n;

    public Matrices() {
        vector= new Vector<Vector<Integer>>();
        fixedRow=0;
        fixedColumn=0;
        level=1;
        position=1;
        bound= Integer.MAX_VALUE;
        n=0;
    }

    public Matrices(Vector<Vector<Integer>> vector, int bound, int fixedRow, int fixedColumn, int level, int position) {
        this.vector = vector;
        this.bound = bound;
        this.fixedRow = fixedRow;
        this.n=0;
        this.fixedColumn = fixedColumn;
        this.level = level;
        this.position = position;
    }

    public int getN() {
        return n;
    }

    public void setN(int n) {
        this.n = n;
    }

    public Vector<Vector<Integer>> getVector() {
        return vector;
    }

    public void setVector(Vector<Vector<Integer>> vector) {
        this.vector = vector;
    }

    public int getBound() {
        return bound;
    }

    public void setBound(int bound) {
        this.bound = bound;
    }

    public int getFixedRow() {
        return fixedRow;
    }

    public void setFixedRow(int fixedRow) {
        this.fixedRow = fixedRow;
    }

    public int getFixedColumn() {
        return fixedColumn;
    }

    public void setFixedColumn(int fixedColumn) {
        this.fixedColumn = fixedColumn;
    }

    public int getLevel() {
        return level;
    }

    public void setLevel(int level) {
        this.level = level;
    }

    public int getPosition() {
        return position;
    }

    public void setPosition(int position) {
        this.position = position;
    }
}
