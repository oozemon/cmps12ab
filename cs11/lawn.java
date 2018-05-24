/* lawn.java
* Usman Zahid
* uzahid
* pa1
* The time it takes to mow a lawn given the dimensions and rate
*/


import java.util.Scanner;

class  lawn{

   public static void main( String[] args ){

      double la_area, l_length, l_width, l_area, h_length;
      double h_width, h_area, mow_rate;
      int h, m, s;
      string filename ="";
      if(args.length >=1){
         filename = args[0];
               Scanner infile = new Scanner(new File(filename));
      }
      Scanner sc = new Scanner(System.in).useDelimiter("\\s");


      System.out.print("Enter the length and width of the lot, in feet: \n");
      l_width = sc.nextDouble();
      l_length = sc.nextDouble();
      l_area = l_width*l_length;
      System.out.print("Enter the length and width of the house, in feet: \n");
      h_width = sc.nextDouble();
      h_length = sc.nextDouble(); 
      h_area = h_width*h_length;
      la_area = l_area - h_area;
      System.out.format("The lawn area is: %1.1f\n", la_area);
      System.out.print("Enter the mowing rate, in square feet per second: \n");
      mow_rate = sc.nextDouble();
      mow_rate = la_area/mow_rate;
      System.out.format("The mowing time is ");
      s = (int) Math.round(mow_rate);
      m = s/60;
      s = s%60;
      h = m/60;
      m = m%60;
      if (h==1 && m==1 && s==1){
            System.out.println(h+" hour, "+m+" minute and "+s+" second");
      }
       else if (h!=1 && m==1 && s==1){
            System.out.println(+h+" hours, "+m+" minute and "+s+" second");
      }
       else if (h==1 && m!=1 && s==1){
            System.out.println(+h+" hour, "+m+" minutes and "+s+" second");
      }
       else if (h==1 && m==1 && s!=1){
            System.out.println(+h+" hour, "+m+" minute and "+s+" seconds");
      }
       else if (h!=1 && m!=1 && s==1){
            System.out.println(+h+" hours, "+m+" minutes and "+s+" second");
      }
       else if (h!=1 && m==1 && s!=1){
            System.out.println(+h+" hours, "+m+" minute and "+s+" seconds");
      }
       else if (h==1 && m!=1 && s!=1){
            System.out.println(+h+" hour, "+m+" minutes and "+s+" seconds");
      }
      else System.out.println(h+" hours, "+m+" minutes and "+s+" seconds");
   }
}