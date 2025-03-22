package Controller;


import Model.BoxStates;
import Model.PartOfShip;

import java.awt.*;
import java.util.ArrayList;
import java.util.Objects;

public class Ship{
  //cada classe en un vaixell i conté tots els seus PartOfShip per poder construir-lo i saber quan enfonses un vaixell
  //aquí s'ha de fer la funció per comprovar que estigui tot el vaixell per poder-la cridar des de la subclasse

  private ArrayList<PartOfShip> childrens;//TODO:
  public void crateShip(int size) {
    if (size >= 2){
      childrens = new ArrayList<>();
      childrens.add(new PartOfShip(BoxStates.END_OF_THE_SHIP));
      for (int i = 1; i < (size - 1); i++) {
        childrens.add(new PartOfShip(BoxStates.MIDDLE_OF_THE_SHIP));
      }
      childrens.add(new PartOfShip(BoxStates.END_OF_THE_SHIP));
    } else {
      childrens = null;
    }
  }

  public boolean isDead(){//1->dead
    for (PartOfShip part : childrens) {
      if (!part.isHit()) {
        return false;
      }
    }
    return true;
  }
  public PartOfShip getPart(int i){
    if(childrens != null)
      if(childrens.size() > i && i > -1)
        return childrens.get(i);
    return null;
  }
  public int getSize(){
    return childrens.size();
  }



}
