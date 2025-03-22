
package base.no.states.groups;
import java.time.DayOfWeek;
import java.time.LocalDate;
import java.time.LocalTime;
import java.util.ArrayList;
import base.no.states.Actions;
import base.no.states.areas.DirectoryAreas;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

//Instantiates all the groups and users
//When creating the group it also adds
//the schedule of each one
//It also adds the user to their
//corresponding group

public final class DirectoryGroup {
    private DirectoryGroup() { }
    private static final Logger LOGGER = LoggerFactory.getLogger("Fita1");
    private static ArrayList<Group> allGroups = new ArrayList<>();
    private static final ArrayList<User> USERS_LIST = new ArrayList<>();
    private static final int START_YEAR = 2023;
    private static final int START_MONTH = 9;
    private static final int START_DAY = 1;
    private static final int START_MONTH_ADMIN = 1;
    private static final int END_YEAR = 2024;
    private static final int END_MONTH = 3;
    private static final int END_DAY = 1;
    private static final int END_YEAR_ADMIN = 2100;
    private static final int END_MONTH_ADMIN = 12;
    private static final int END_DAY_ADMIN = 31;
    private static final int START_HOUR = 9;
    private static final int START_MINUTE = 0;
    private static final int END_HOUR = 17;
    private static final int END_MINUTE = 0;
    private static final int START_HOUR_MANAGER = 8;
    private static final int START_MINUTE_MANAGER = 0;
    private static final int END_HOUR_MANAGER = 20;
    private static final int END_MINUTE_MANAGER = 0;
    private static final int START_HOUR_ADMIN = 0;
    private static final int START_MINUTE_ADMIN = 0;
    private static final int END_HOUR_ADMIN = 23;
    private static final int END_MINUTE_ADMIN = 59;
    public static void makeGroups() {
        Group administrator = new Group("Administrator");
        allGroups.add(administrator);
        Group manager = new Group("Manager");
        allGroups.add(manager);
        Group employee = new Group("Employee");
        allGroups.add(employee);
        Group blank = new Group("Blank");
        allGroups.add(blank);
        blank.setSchedule(null);

        // users without any privilege, just to keep temporally
        // users instead of deleting them, this is to withdraw all
        // permissions but still to keep user data to give back
        // permissions later
        User bernat = new User("Bernat", "12345", blank);
        USERS_LIST.add(bernat);
        blank.addAtGroup(bernat);
        User blai = new User("Blai", "77532", blank);
        USERS_LIST.add(blai);
        blank.addAtGroup(blai);

        // employees :
        // Sep. 1 2023 to Mar. 1 2024
        // week days 9-17h
        // just shortly unlock
        // ground floor, floor1, exterior,
        // stairs (this, for all), that is, everywhere but the parking
        User ernest = new User("Ernest", "74984", employee);
        USERS_LIST.add(ernest);
        User eulalia = new User("Eulalia", "43295", employee);
        USERS_LIST.add(eulalia);

        employee.addAtGroup(ernest);
        employee.addAtGroup(eulalia);

        employee.addArea(DirectoryAreas.findAreaById("ground_floor"));
        employee.addArea(DirectoryAreas.findAreaById("floor1"));
        employee.addArea(DirectoryAreas.findAreaById("exterior"));
        employee.addArea(DirectoryAreas.findAreaById("stairs"));



        LocalDate employeeStartDate = LocalDate.of(
                START_YEAR, START_MONTH, START_DAY);
        LocalDate employeeEndDate = LocalDate.of(END_YEAR, END_MONTH, END_DAY);

        LocalTime employeeStartTime = LocalTime.of(START_HOUR, START_MINUTE);
        LocalTime employeeEndTime = LocalTime.of(END_HOUR, END_MINUTE);

        ArrayList<DayOfWeek> employeeDaysOfTheWeek = new ArrayList<>();
        employeeDaysOfTheWeek.add(DayOfWeek.MONDAY);
        employeeDaysOfTheWeek.add(DayOfWeek.TUESDAY);
        employeeDaysOfTheWeek.add(DayOfWeek.WEDNESDAY);
        employeeDaysOfTheWeek.add(DayOfWeek.THURSDAY);
        employeeDaysOfTheWeek.add(DayOfWeek.FRIDAY);
        Schedule scheduleEmployer = new Schedule(
                employeeStartDate, employeeEndDate,
                employeeStartTime, employeeEndTime,
                employeeDaysOfTheWeek);

        employee.setSchedule(scheduleEmployer);

        employee.addAction(Actions.OPEN);
        employee.addAction(Actions.CLOSE);
        employee.addAction(Actions.UNLOCK_SHORTLY);

        // managers :
        // Sep. 1 2023 to Mar. 1 2024
        // week days + saturday, 8-20h
        // all actions
        // all spaces
        User manel = new User("Manel", "95783", manager);
        USERS_LIST.add(manel);
        manager.addAtGroup(manel);
        User marta = new User("Marta", "05827", manager);
        USERS_LIST.add(marta);
        manager.addAtGroup(marta);
        manager.addArea(DirectoryAreas.findAreaById("building"));

        LocalDate managerStartDate = LocalDate.of(
                START_YEAR, START_MONTH, START_DAY);
        LocalDate managerEndDate = LocalDate.of(END_YEAR, END_MONTH, END_DAY);

        LocalTime managerStartTime = LocalTime.of(
                START_HOUR_MANAGER, START_MINUTE_MANAGER);
        LocalTime managerEndTime = LocalTime.of(
                END_HOUR_MANAGER, END_MINUTE_MANAGER);

        ArrayList<DayOfWeek> managerDaysOfTheWeek = new ArrayList<>();
        managerDaysOfTheWeek.add(DayOfWeek.MONDAY);
        managerDaysOfTheWeek.add(DayOfWeek.TUESDAY);
        managerDaysOfTheWeek.add(DayOfWeek.WEDNESDAY);
        managerDaysOfTheWeek.add(DayOfWeek.THURSDAY);
        managerDaysOfTheWeek.add(DayOfWeek.FRIDAY);
        managerDaysOfTheWeek.add(DayOfWeek.SATURDAY);
        Schedule scheduleManager = new Schedule(
                managerStartDate, managerEndDate,
                managerStartTime, managerEndTime,
                managerDaysOfTheWeek);

        manager.setSchedule(scheduleManager);

        manager.addAction(Actions.LOCK);
        manager.addAction(Actions.UNLOCK);
        manager.addAction(Actions.UNLOCK_SHORTLY);
        manager.addAction(Actions.OPEN);
        manager.addAction(Actions.CLOSE);

        // admin :
        // always=2023 to 2100
        // all days of the week
        // all actions
        // all spaces
        User ana = new User("Ana", "11343", administrator);
        USERS_LIST.add(ana);
        administrator.addAtGroup(ana);
        administrator.addArea(DirectoryAreas.findAreaById("building"));

        LocalDate adminStartDate = LocalDate.of(
                START_YEAR, START_MONTH_ADMIN, START_DAY);
        LocalDate adminEndDate = LocalDate.of(
                END_YEAR_ADMIN, END_MONTH_ADMIN, END_DAY_ADMIN);

        LocalTime adminStartTime = LocalTime.of(
                START_HOUR_ADMIN, START_MINUTE_ADMIN);
        LocalTime adminEndTime = LocalTime.of(
                END_HOUR_ADMIN, END_MINUTE_ADMIN);

        ArrayList<DayOfWeek> adminDaysOfTheWeek = new ArrayList<>();
        adminDaysOfTheWeek.add(DayOfWeek.MONDAY);
        adminDaysOfTheWeek.add(DayOfWeek.TUESDAY);
        adminDaysOfTheWeek.add(DayOfWeek.WEDNESDAY);
        adminDaysOfTheWeek.add(DayOfWeek.THURSDAY);
        adminDaysOfTheWeek.add(DayOfWeek.FRIDAY);
        adminDaysOfTheWeek.add(DayOfWeek.SATURDAY);
        adminDaysOfTheWeek.add(DayOfWeek.SUNDAY);

        Schedule scheduleAdmin = new Schedule(adminStartDate, adminEndDate,
                                             adminStartTime, adminEndTime,
                                             adminDaysOfTheWeek);

        administrator.setSchedule(scheduleAdmin);

        administrator.addAction(Actions.LOCK);
        administrator.addAction(Actions.UNLOCK);
        administrator.addAction(Actions.UNLOCK_SHORTLY);
        administrator.addAction(Actions.OPEN);
        administrator.addAction(Actions.CLOSE);
    }
    public static User findUserByCredential(final String credential) {
        for (User user : USERS_LIST) {
            if (user.getCredential().equals(credential)) {
                return user;
            }
        }
        LOGGER.error("user with credential " + credential + " not found");
        return null; // otherwise we get a Java error
    }
}
