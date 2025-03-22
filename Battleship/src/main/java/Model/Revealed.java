package Model;

public class Revealed implements Box {//indica que la casella ha estat revelada ("el jugador a tirar una bomba")
  public Revealed() { }

  //retorna la casella real (per poder fer aixo s'ha de pasar per parametre el tauer resolt del enemic??????) (retornar quina casella es la adequada (s'ha de cridarn el get de la casella aigua o port of sip corresponen per que retorni i retornar)???????)
  @Override
  public String getContentsOfBox(Box boxResolved){
    if (boxResolved != null) {
      if ((boxResolved.getClass() == Water.class) || (boxResolved.getClass() == PartOfShip.class)) {
        return boxResolved.getContentsOfBox(boxResolved);
      }
    }
    return BoxStates.ERROR;
  }
}
