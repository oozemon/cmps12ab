class Complex{
   //--------------------------------------------------------------------------
   // Private Data Fields 
   //--------------------------------------------------------------------------
   private double re;
   private double im;
   private double [] CArray;
   //--------------------------------------------------------------------------
   // Public Constant Fields 
   //--------------------------------------------------------------------------
   public static final Complex ONE = Complex.valueOf(1,0);
   public static final Complex ZERO = Complex.valueOf(0,0);
   public static final Complex I = Complex.valueOf(0,1);

   //--------------------------------------------------------------------------
   // Constructors 
   //--------------------------------------------------------------------------
   Complex(double a, double b){
      this.re = a;
      this.im = b;
   }

   Complex(double a){
      this.re = a;
      this.im = 0;
   }
   Complex(String s){
	   CArray = parseComplex(s);
	   this.re = CArray [0];
	   this.im = CArray [1];
	  
   }

   static double[] parseComplex(String str){
	      double[] part = new double[2];
	      String s = str.trim();
	      String NUM = "(\\d+\\.\\d*|\\.?\\d+)";
	      String SGN = "[+-]?";
	      String OP =  "\\s*[+-]\\s*";
	      String I =   "i";
	      String OR =  "|";
	      String REAL = SGN+NUM;
	      String IMAG = SGN+NUM+"?"+I;
	      String COMP = REAL+OR+
	                    IMAG+OR+
	                    REAL+OP+NUM+"?"+I;
	      
	      if( !s.matches(COMP) ){
	         throw new NumberFormatException(
	                   "Cannot parse input string \""+s+"\" as Complex");
	      }
	      s = s.replaceAll("\\s","");     
	      if( s.matches(REAL) ){
	         part[0] = Double.parseDouble(s);
	         part[1] = 0;
	      }else if( s.matches(SGN+I) ){
	         part[0] = 0;
	         part[1] = Double.parseDouble( s.replace( I, "1.0" ) );
	      }else if( s.matches(IMAG) ){
	         part[0] = 0;
	         part[1] = Double.parseDouble( s.replace( I , "" ) );
	      }else if( s.matches(REAL+OP+I) ){
	         part[0] = Double.parseDouble( s.replaceAll( "("+REAL+")"+OP+".+" , "$1" ) );
	         part[1] = Double.parseDouble( s.replaceAll( ".+("+OP+")"+I , "$1"+"1.0" ) );
	      }else{   //  s.matches(REAL+OP+NUM+I) 
	         part[0] = Double.parseDouble( s.replaceAll( "("+REAL+").+"  , "$1" ) );
	         part[1] = Double.parseDouble( s.replaceAll( ".+("+OP+NUM+")"+I , "$1" ) );
	      }
	      return part;
	   }
   //---------------------------------------------------------------------------
   // Public methods 
   //---------------------------------------------------------------------------

   // Complex arithmetic -------------------------------------------------------

   // copy()
   // Return a new Complex equal to this Complex
   Complex copy(){
	   double recopy, imcopy;
	   recopy = this.re;
	   imcopy = this.im;
	   Complex copy = new Complex(recopy, imcopy);
	   return copy;
   }
   
   // add()
   // Return a new Complex representing the sum this plus z.
   Complex add(Complex z){
	   double readd, imadd;
	   readd = this.re + z.re;
	   imadd = this.im + z.im;
      Complex add = new Complex(readd,imadd);
      return add;
      
   }
   
   // negate()
   // Return a new Complex representing the negative of this.
   Complex negate(){
      double reneg, imneg;
      reneg = this.re * (-1);
      imneg = this.im * (-1);
      Complex negative = new Complex(reneg, imneg);
      return negative;
   }

   // sub()
   // Return a new Complex representing the difference this minus z.
   Complex sub(Complex z){
      double resub, imsub;
      resub = this.re - z.re;
      imsub = this.im - z.im;
      Complex subtract = new Complex(resub, imsub);
      return subtract;
   }

   // mult()
   // Return a new Complex representing the product this times z.
   Complex mult(Complex z){
      double remult, immult;
      remult = (this.re * z.re) -(this.im*z.im);
      immult = (this. re* z.im) + (this.im *z.re) ;
      Complex multiply = new Complex (remult, immult);
      return multiply;
   }

   // recip()
   // Return a new Complex representing the reciprocal of this.
   // Throw an ArithmeticException with appropriate message if 
   // this.equals(Complex.ZERO).
   Complex recip(){
      double rerecip, imrecip;
      rerecip = (this.re/((Math.pow(this.re,2)) + Math.pow(this.im, 2)));
      imrecip = (this.im/((Math.pow(this.re,2)) + Math.pow(this.im, 2)));
      Complex reciprocal = new Complex(rerecip,imrecip);
      return reciprocal;
   }

   // div()
   // Return a new Complex representing the quotient of this by z.
   // Throw an ArithmeticException with appropriate message if 
   // z.equals(Complex.ZERO).
   Complex div(Complex z){
     Complex reDiv;
     reDiv = this.mult(z.recip());
     try {
    	 z.equals(Complex.ZERO);
     }catch (ArithmeticException ae){
    	 System.out.println("ArithmeticException Occured!");
     }
     return reDiv;
   }

   // conj()
   // Return a new Complex representing the conjugate of this Complex.
   Complex conj(){
      double reconj, imconj;
      reconj = this.re * (-1);
      imconj = this.im *(-1);
      Complex conjugate = new Complex (reconj, imconj);
      return conjugate;
   }
   
   // Re()
   // Return the real part of this.
   double Re(){
      return re;
   }

   // Im()
   // Return the imaginary part of this.
   double Im(){
      return im;
   }

   // abs()
   // Return the modulus of this Complex, i.e. the distance between 
   // points (0, 0) and (re, im).
   double abs(){
      return Math.hypot(this.re, this.im);
   }

   // arg()
   // Return the argument of this Complex, i.e. the angle this Complex
   // makes with positive real axis.
   double arg(){
      return Math.atan2(im, re);
   }

   // Other functions ---------------------------------------------------------
   
   // toString()
   // Return a String representation of this Complex.
   // The String returned will be readable by the constructor Complex(String s)
   public String toString(){
       String Zero = "0.0";
       String str = "";
        if(this.re < 0){
          str += String.valueOf(this.re);
        }else if(this.re > 0){
          str += "" + String.valueOf(this.re);
        }else{
          str += "";
        }
        if(this.im < 0){
          str += String.valueOf(this.im) + "i";
        } else if(this.re == 0 && this.im > 0){
          str += "" + String.valueOf(this.im) + "i";
        }else if(this.im > 0){
          str += "+" + String.valueOf(this.im) + "i";
        }else{  
          str += "";
        }

        return str;  
     
   }

   // equals()
   // Return true iff this and obj have the same real and imaginary parts.
   public boolean equals(Object obj){
	      boolean a = false;
	      boolean b = false;
	      Complex temp = (Complex) obj;
	      
	      if(this.re == temp.re){
	      	a = true;
	      }else{
	      	a = false;
	      }
	      if(this.im == temp.im){
	      	b = true;
	      }else{
	 		b = false;
	 	}
	 	
	 	if(a == true && b == true){
	 		return true;
	 		}else{
	 		return false;
	 		}
   }

   // valueOf()
   // Return a new Complex with real part a and imaginary part b.
   static Complex valueOf(double a, double b){
      return new Complex (a,b);
   }

   // valueOf()
   // Return a new Complex with real part a and imaginary part 0.
   static Complex valueOf(double a){
      return new Complex (a,0);
   }

   // valueOf()
   // Return a new Complex constructed from s.
   static Complex valueOf(String s){
      return new Complex (s);
   }

}