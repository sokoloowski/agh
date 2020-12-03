public class Main {
    public static void main(String[] args){
        System.out.println("Drzewko:");
        Przyklad p = new Przyklad();
        p.wypisz(5);

        System.out.println();
        System.out.println("Odwrotne drzewko:");
        p.wypiszOdwrotnie(5);
    }
}
