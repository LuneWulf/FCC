# FCC
Fire Control Console, automatic fire solution console for arma 3.

Will possibly be made into a GUI with GTK or using ARMA 3s own scripting language SQF to allow in game use. TBD.


Currently the console allows for the following:

Calculation of firing solutions given:

- Ammo details (Muzzel velocity per charge and in game drag coefficient, normally 0.00006)
- Gun grids and elevations.
- Aimpoints that define a sheaf:
    - Parallel (Gives a singular global high and low solution based on the "middle" guns position)
    - Converged (Gives a high and low solution unique to each gun to hit the same point)
    - Open (Gives a high and low solution unique to each gun to hit a point which is an effective burst diameter to the side of the aimpoint)
    - Linear (Gives evenly spaced out aimpoints for each gun along a line designated either by two bounding grids or a length and an attitude (direction))
    - Rectangular (Gives evenly spaced out aimpoints along two "rails" which are parallel to the given attitude with a given length)
    - Circular (Gives evenly spaced out aimpoints along a concentric circle of half the provided radius)
    - Irregular (Gives evenly spaced out aimpoints on the lines connecting the aimpoints)
- Atmospheric data (Temperature, humidity in decimal form, pressure and wind speed and direction)
- Charge specified by user or found automatically.

Future additions:
- Airburst munition fires.
- Different target references.
  - Grid,
  - Polar,
  - TRPs, and
  - Previous targets
- Amount of rounds needed, then distributed amongst the guns
  - Possibly with the addition of specifying exactly which guns are participating in the fire.
- Time on target.
  - Automatically calculate the time at which fires should be initiated to allow for a specific time on target instead of manually calculating this.
- Adjustments relative to FO
  - This requires knowledge of FO position.
  - Adjustments are given as ADD/DROPP/LEFT/RIGHT relative to observer
- For linear and rectangular sheafs, possibly use aimpoint as a marker of the targets middle instead of one of the ends.