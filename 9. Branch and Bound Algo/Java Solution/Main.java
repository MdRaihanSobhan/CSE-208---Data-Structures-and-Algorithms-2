import java.security.cert.TrustAnchor;
import java.util.Scanner;
import java.util.Vector;

public class Main {

    public int countUnfixBound(int n, Vector<Vector<Integer>> vector){
        int rowBand=0;
        int colBand=0;
        int maxBound=0;
        for(int i=0; i<n; i++){
            rowBand=0;
            colBand=0;
            for(int j=0; j<n; j++){
                rowBand+= vector.get(i).get(j);
                colBand+=vector.get(j).get(i);
            }
            // System.out.println(rowBand+ " "+ colBand);
            maxBound= Math.max(maxBound, rowBand);
            maxBound= Math.max(maxBound, colBand);
        }
        maxBound++;
        maxBound/=2;
        return maxBound;
    }

    public static void main(String[] args) {
        int solutionBound=0;
        int n;
        char ch;
        int maxBound=0;
        int count =0;
        Main main= new Main();
        Vector<Matrices> matrices = new Vector<Matrices>();
        Vector<Vector<Integer>> tempMatrix = new Vector<Vector<Integer>>();

        Matrices solutionMatrix = new Matrices();

        Scanner scanner= new Scanner(System.in);
        n= scanner.nextInt();


        for(int i=0;i<n;i++){
            tempMatrix.add(new Vector<Integer>());
            for(int j=0; j<n; j++){
                tempMatrix.get(i).add(0);
            }
        }

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                ch= scanner.next().charAt(0);
                if(ch=='X'){
                    tempMatrix.get(i).set(j,1 );
                }
                else{
                    tempMatrix.get(i).set(j,0);
                }
            }
        }


        maxBound= main.countUnfixBound(n,tempMatrix);

        Matrices mat= new Matrices(tempMatrix, maxBound, 0, 0, 1, 1);

        matrices.add(mat);

        //int nn=0;

        while (true){

            //nn++;
            //if(nn>100) break;


            int fixedRow;
            int fixedColumn;

            int lowerBound= Integer.MAX_VALUE;
            int finalBound= -1;

            int level=-1;
            int position=-1;

            for(int i=0; i<matrices.size(); i++){
                if(matrices.get(i).getBound()< lowerBound) lowerBound=matrices.get(i).getBound();
            }

            for(int i=0; i<matrices.size(); i++){
                if(matrices.get(i).getBound()== lowerBound){
                    if(matrices.get(i).getLevel()>level){
                        level= matrices.get(i).getLevel();
                    }
                }
            }
            for(int i=0; i<matrices.size(); i++){
                if(matrices.get(i).getBound()==lowerBound){
                    if(matrices.get(i).getLevel()==level){
                        if(matrices.get(i).getPosition()>position){
                            position= matrices.get(i).getPosition();
                        }
                    }
                }
            }

            Matrices mat1= new Matrices();
            for(int i=0; i< matrices.size(); i++){
                if(matrices.get(i).getBound()==lowerBound){
                    if(matrices.get(i).getLevel()== level){
                        if(matrices.get(i).getPosition()==position){
                            mat1= matrices.get(i);
                            matrices.get(i).setBound(Integer.MAX_VALUE);
                            break;
                        }
                    }
                }
            }

            level= mat1.getLevel()+1;
            fixedRow= mat1.getFixedRow();
            fixedColumn=mat1.getFixedColumn();

            if(fixedRow== n-1  && fixedColumn==n-1){
                solutionMatrix= mat1;
                break;
            }

            Vector<Vector<Integer>> v1 = mat1.getVector();

            if(fixedRow== fixedColumn-1){
                for (int k=1; k<= (n-fixedRow); k++){
                    Vector<Vector<Integer>> v2 = new Vector<Vector<Integer>>();
                    for(int i=0;i<n;i++){
                        v2.add(new Vector<Integer>());
                        for(int j=0; j<n; j++){
                            v2.get(i).add(0);
                        }
                    }

                    for(int j=0; j<fixedRow; j++){
                        for(int i=0; i<n; i++){
                            int a = v1.get(j).get(i);
                            v2.get(j).set(i,a);
                        }
                    }

                    for(int i=0; i<n; i++){
                        int a= v1.get(fixedRow+ k - 1).get(i);
                        v2.get(fixedRow).set(i, a);
                    }

                    for(int j = fixedRow+1, swapCheck=1;  j<n; j++, swapCheck++){
                        if(swapCheck==k) swapCheck++;

                        for(int i=0; i<n; i++){
                            int a= v1.get(fixedRow+swapCheck-1).get(i);
                            v2.get(j).set(i,a);
                        }
                    }

                    finalBound= -1;
                    int newFixedRow = fixedRow + 1;
                    int bam;
                    int dan;

                    for(int i=0; i<newFixedRow; i++){
                        bam= i;
                        for(int j=0; j<i; j++){
                            if(v2.get(i).get(j)==1){
                                bam=j;
                                break;
                            }
                        }
                        dan=i;
                        for(int j= fixedColumn-1; j>i; j--){
                            if(v2.get(i).get(j)==1){
                                dan=j;
                                break;
                            }
                        }

                        int cnt= 0;

                        for(int j= fixedColumn; j<n; j++){
                            if(v2.get(i).get(j)==1) cnt++;
                        }

                        if(cnt>0) dan= fixedColumn+cnt-1 ;

                        int a= i-bam+1;
                        int b= dan-i+1;

                        finalBound= Math.max(finalBound, Math.max(a,b ));

                    }


                    for (int i=0; i<fixedColumn; i++){
                        bam=i;
                        for(int j=0; j<i; j++){
                            if(v2.get(j).get(i)==1){
                                bam=j;
                                break;
                            }
                        }
                        dan=i;
                        for (int j= newFixedRow-1; j>i; j--){
                            if(v2.get(j).get(i)==1){
                                dan=j;
                                break;
                            }
                        }

                        int cnt=0;
                        for(int j= newFixedRow; j<n; j++){
                            if(v2.get(j).get(i)==1) cnt++;
                        }
                        if(cnt>0){
                            dan= newFixedRow + cnt - 1;
                        }
                        int a= i-bam+1;
                        int b= dan-i+1;

                        finalBound= Math.max(finalBound, Math.max(a,b ));

                    }
                    maxBound=-1;

                    for(int i= newFixedRow; i<n; i++){
                        count=0;
                        for(int j= fixedColumn; j<n; j++){
                            count+= v2.get(i).get(j);
                        }
                        if(maxBound<count) maxBound= count;
                    }

                    for(int j= fixedColumn; j<n; j++){
                        count=0;
                        for (int i=newFixedRow; i<n; i++){
                            count+= v2.get(i).get(j);
                        }
                        if(maxBound<count) maxBound=count;
                    }

                    maxBound++;
                    maxBound/=2;
                    finalBound = Math.max(finalBound, maxBound);
                    Matrices m= new Matrices(v2, finalBound, fixedRow, newFixedRow, level, k);
                    matrices.add(m);

                }
            }

            else {
                for (int col=1; col<= (n-fixedColumn); col++){
                    Vector<Vector<Integer>> v2 = new Vector<Vector<Integer>>();
                    for(int i=0;i<n;i++){
                        v2.add(new Vector<Integer>());
                        for(int j=0; j<n; j++){
                            v2.get(i).add(0);
                        }
                    }

                    for(int j=0; j<fixedColumn; j++){
                        for(int i=0; i<n; i++){
                            int a = v1.get(i).get(j);
                            v2.get(i).set(j,a);
                        }
                    }

                    for(int i=0; i<n; i++){
                        int a= v1.get(i).get(fixedColumn+ col - 1);
                        v2.get(i).set(fixedColumn, a);
                    }

                    for(int j = fixedColumn+1, p=1;  j<n; j++, p++){
                        if(p==col) p++;

                        for(int i=0; i<n; i++){
                            int a= v1.get(i).get(fixedColumn+ p - 1);
                            v2.get(i).set(j,a);
                        }
                    }

                    finalBound= -1;
                    int newFixedColoumn = fixedColumn + 1;
                    int bam, dan;

                    for(int i=0; i<fixedRow; i++){
                        bam= i;
                        for(int j=0; j<i; j++){
                            if(v2.get(i).get(j)==1){
                                bam=j;
                                break;
                            }
                        }
                        dan=i;
                        for(int j= newFixedColoumn-1; j>i; j--){
                            if(v2.get(i).get(j)==1){
                                dan=j;
                                break;
                            }
                        }

                        int cntX= 0;

                        for(int j= newFixedColoumn; j<n; j++){
                            if(v2.get(i).get(j)==1) cntX++;
                        }

                        if(cntX>0) dan= newFixedColoumn+cntX-1 ;

                        int a= i-bam+1;
                        int b= dan-i+1;

                        finalBound= Math.max(finalBound, Math.max(a,b ));

                    }


                    for (int i=0; i<newFixedColoumn; i++){
                        bam=i;
                        for(int j=0; j<i; j++){
                            if(v2.get(j).get(i)==1){
                                bam=j;
                                break;
                            }
                        }
                        dan=i;
                        for (int j= fixedRow-1; j>i; j--){
                            if(v2.get(j).get(i)==1){
                                dan=j;
                                break;
                            }
                        }

                        int cnt=0;
                        for(int j= fixedRow; j<n; j++){
                            if(v2.get(j).get(i)==1) cnt++;
                        }
                        if(cnt>0){
                            dan= fixedRow + cnt - 1;
                        }
                        int a= i-bam+1;
                        int b= dan-i+1;

                        finalBound= Math.max(finalBound, Math.max(a,b ));

                    }
                    maxBound=0;

                    for(int i= fixedRow; i<n; i++){
                        count=0;
                        for(int j= newFixedColoumn; j<n; j++){
                            count+= v2.get(i).get(j);
                        }
                        if(maxBound<count) maxBound= count;
                    }

                    for(int j= newFixedColoumn; j<n; j++){
                        count=0;
                        for (int i=fixedRow; i<n; i++){
                            count+= v2.get(i).get(j);
                        }
                        if(maxBound<count) maxBound=count;
                    }

                    maxBound++;
                    maxBound/=2;
                    finalBound = Math.max(finalBound, maxBound);
                    Matrices m= new Matrices(v2, finalBound, fixedRow, newFixedColoumn, level, col);
                    matrices.add(m);

                }

            }


        }

        Vector<Vector<Integer>> temp;
        temp= solutionMatrix.getVector();
        System.out.println(solutionMatrix.getBound());

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(solutionMatrix.getVector().get(i).get(j)==1){
                    System.out.print("X ");
                }
                else{
                    System.out.print("0 ");
                }
                System.out.println();
            }
        }



        System.out.println(maxBound);

        for(int i=0;i<n;i++){
            for(int j=0; j<n;j++){
                System.out.print(temp.get(i).get(j) + " ");
            }
            System.out.println();
        }
        System.out.println();



    }
}

/*
4
X 0 0 X
0 0 X 0
X 0 0 X
0 X X X
        */