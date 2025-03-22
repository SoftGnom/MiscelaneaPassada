package Model;

public interface Box {//casella de la cuadricula del joc

  //consulta el contingut
  //boxResolved-> null: casella del tauler complet amb les solucions
  //boxResolved-> Box: casella del tauler parcialment complet amb les solucions
  public String getContentsOfBox(Box boxResolved);

}
