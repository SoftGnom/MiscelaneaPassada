package Model;

import Controller.Ship;

public class PartOfShip extends Ship implements Box {
  private String part;
  private boolean hit;//1->hit
  public PartOfShip(String part){
    this.hit = false;
    this.part = part;
  }

  //retornar la part del vaixell
  @Override
  public String getContentsOfBox(Box boxResolved){
    return part;
  }

  //s'ha destruit el tros de vaixell
  public void shoot() { hit = true; }
  public boolean isHit() { return hit; }
}

