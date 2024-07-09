import java.io.File;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        RB_Tree rbt= new RB_Tree();
        // File input= new File("/Users/md.raihansobhan/Documents/BUET/CSE204/Java Projects/RB_Tree/src/input.txt");

        File input= new File("src/input.txt");



        try{
            Scanner scanner = new Scanner(input);

            int t= scanner.nextInt();
            System.out.println(t);

            for(int i=0; i<t; i++){
                int operation = scanner.nextInt();
                int data= scanner.nextInt();
                if(operation==0){
                    System.out.println(operation+ " " + data + " " + rbt.RB_Delete(data));
                }
                else if(operation==1){
                    System.out.println(operation+ " " + data + " " + rbt.RB_Insert(data));
                }
                else if(operation==2){
                    System.out.println(operation+ " " + data + " " + rbt.RB_Find(data));
                }
                else if(operation==3){
                    // System.out.println(operation+ " " + data + " " +rbt.priorityCount(rbt.getRootNode(), 0,data-1));
                    System.out.println(operation+ " " + data + " " +rbt.countLowers(rbt.getRootNode(), data));
                }
            }

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
