CALINA CRISTIAN FLORIN 333CA

Am implementat tema folosind SFML. (Am lucrat in Visual Studio)
Arhiva am facut-o astfel incat sa poata fi deschis fisierul .sln si sa functioneze corect
A trebuit sa introduc dependentele si am facut o legare dinamica(am introdus fisierele 
necesare in proiect. Le-am adaugat si in arhiva in caz ca e nevoie).
Pentru detalii de implementare am pus comentarii in cod.
Pentru trasarea razei am crescut treptat y-ul la fiecare frame si am salvat
x-ul si y-ul luand in considerare rotatia in variabila onx.
Scena este un dreptunghi de dimensiunea ferestrei asa cum este specificat in cerinta.
Camera este un triunghi pus in coltul dreapta sus al scenei.
Obiectele le-am generat printr-un vector si pozitia lor am pus-o aleator folosind mod 
pe iterator alaturi de niste numere alese random de mine.
Raza de lumina se opreste din crescut odata ce loveste camera sau se reflecta de 19 ori.
Aceasta este un vector cu un counter global care creste la fiecare reflexie si se reseteaza
la apasari de sageata dreapta/stanga incepand redesenearea primei raze (practic se suprascrie
vectorul si se redeseneaza doar primele reflectionCounter elemente la fiecare resetare).