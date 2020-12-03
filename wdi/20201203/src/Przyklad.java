public class Przyklad {
    public void wypisz(int liczbaLinii) {
        for (int i = 1; i <= liczbaLinii; i++) {
            for (int j = (liczbaLinii - i); j > 0; j--) {
                System.out.print(" ");
            }
            for (int j = 1; j < (i * 2); j++) {
                System.out.print("*");
            }
            System.out.println("");
        }
    }

    public void wypiszOdwrotnie(int liczbaLinii) {
        for (int i = liczbaLinii; i > 0; i--) {
            for (int j = (liczbaLinii - i); j > 0; j--) {
                System.out.print(" ");
            }
            for (int j = 1; j < (i * 2); j++) {
                System.out.print("*");
            }
            System.out.println("");
        }
    }
}
