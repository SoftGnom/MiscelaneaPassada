
package base.no.states.groups;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.time.DayOfWeek;
import java.util.ArrayList;

//This class controlls the schedules of each group
//it permits or denied actions given the time

public class Schedule {
  private static final Logger LOGGER = LoggerFactory.getLogger("Fita1");
  private LocalDate startDate;
  private LocalDate endDate;
  private ArrayList<DayOfWeek> eligibleDays;
  private LocalTime startTime;
  private LocalTime endTime;
  public Schedule() { }
  public Schedule(final LocalDate consStartDate, final LocalDate consEndDate,
                  final LocalTime consStartTime, final LocalTime consEndTime,
                  final ArrayList<DayOfWeek> consEligibleDays) {
    this.startDate = consStartDate;
    this.endDate = consEndDate;
    this.startTime = consStartTime;
    this.endTime = consEndTime;
    this.eligibleDays = consEligibleDays;
  }
  public boolean isAuthorized(final LocalDateTime now) {
    if ((startDate.compareTo(now.toLocalDate()) <= 0)
            && (now.toLocalDate().compareTo(endDate) <= 0)) {
      //is in the time bracket (calendar)
      if ((startTime.compareTo(now.toLocalTime()) <= 0)
              && (now.toLocalTime().compareTo(endTime) <= 0)) {
        //it's during working hours
        if (eligibleDays.contains(now.toLocalDate().getDayOfWeek())) {
          //it's the day of the work week
          return true;
        } else {
          LOGGER.warn("it is not the correct day of the week");
          return false;
        }
      } else {
        LOGGER.warn("it is not the correct schedule time");
        return false;
      }
    } else {
      LOGGER.warn("it is not the day of the correct calendar");
      return false;
    }
  }
}
