%$Id: functions.pl,v 1.3 2016-11-08 15:04:13-08 - - $
% Usman Zahid uzahid@ucsc.edu
% CMPS 112 Asg 4 

mathfns( X, List ) :-
   S is sin( X ),
   C is cos( X ),
   Q is sqrt( X ),
   List = [S, C, Q].

%logical not function from not.pl
not( X ) :- X, !, fail.
   not( _ ).

degmins_in_rads( degmin( Degrees, Minutes ),  Rads ) :-
   Degreedis is Degrees + Minutes / 60,
   Rads is Degreedis * pi / 180.


% implements haversine formula 
haversine_radians( Lat1, Lon1, Lat2, Lon2, Distance ) :-
   degmins_in_rads( Lat1, RadianLat1 ),
   degmins_in_rads( Lon1, RadianLon1 ),
   degmins_in_rads( Lat2, RadianLat2 ),
   degmins_in_rads( Lon2, RadianLon2 ),    
   Dlon is RadianLon2 - RadianLon1,
   Dlat is RadianLat2 - RadianLat1,
   A is sin( Dlat / 2 ) ** 2
      + cos( RadianLat1 ) * cos( RadianLat2 ) * sin( Dlon / 2 ) ** 2,
   Dist is 2 * atan2( sqrt( A ), sqrt( 1 - A )),
   Distance is Dist * 3961.

% finds the time for a flight in hours as a decimal value
time_for_flight( Airport1, Airport2, TimeforFlight ) :-
   airport( Airport1, _, Lat1, Lon1),
   airport( Airport2, _, Lat2, Lon2),
   haversine_radians( Lat1, Lon1, Lat2, Lon2, Distance), 
   TimeforFlight is Distance / 500. 

% function used in makepath to convert values in hours
time_for_arrival( flight( Airport1, Airport2, time( DHours, DMins)),  TArr ) :-
   time_for_flight( Airport1, Airport2, TFlight ), 
   TDeparture is DHours + DMins / 60,
   TArr is TDeparture + TFlight. 

% converts flight time to a decimal value
flighthours( time(Hours, Mins), HoursDec) :-
   HoursDec is Hours + Mins / 60.

convert_to_minutes( Hours, Mins) :-
   Mins is Hours * 60.

convert_to_hours( Hours, Mins, SumHM) :-
   SumHM is Hours + Mins / 60. 
   %write ('SumH is: '), print( SumH).

% makes sure flights are not within 30 minutes or less from one another
valid_time( Hours1, time( X1, Y1)) :-
   convert_to_hours( X1, Y1, Hours2 ),
   convert_to_minutes( Hours1, Minutes1 ),
   convert_to_minutes( Hours2, Minutes2 ),
   Minutes1 + 30 =< Minutes2. 




% make sure no flights are overnight
overnight_check( flight( Departure, Arrival, DepTime)) :-
   time_for_arrival( flight( Departure, Arrival, DepTime), ValidTime),
   ValidTime < 24.

% print digits in "00" string format
print_full_digits(Digits) :-
   Digits <10, print(0), print(Digits).

print_full_digits(Digits) :- 
   Digits >= 10,
   print(Digits).

print_flight_time( HoursMins ) :-
   HoursM is floor( HoursMins * 60),
   Hours is HoursM // 60, 
   Mins is HoursM mod 60,
   print_full_digits(Hours),
   print( ':' ),
   print_full_digits(Mins).

%print_airline( airport(Depart, Arrive), DName, AName) :-
%   Dname is airport(Depart, _),
%   AName is airport(Arrive, _), 
%   format( 'Depart %s %s', airport( Depart, _), [Depart, DName]), nl,

%   format( 'Arrival %s %s', airport( _, Arrive), [Arrive, AName]), nl.


%write path adapted from graphpath.pl
writepath( [] ).  

writepath( [flight(Departure, Arrival, time(DepH, DepM))|List]) :-
   airport( Departure, DName, _, _),
   airport( Arrival, AName, _, _),
   convert_to_hours( DepH, DepM, DepartureTime),
   time_for_arrival( flight(Departure, Arrival, time(DepH, DepM)), ArrivalTime),
   format( 'Depart %s %s  ', [Departure, DName]),
   print_flight_time( DepartureTime),  nl,
   format( 'Arrive %s %s  ', [Arrival, AName]), 
   print_flight_time( ArrivalTime ), nl,
   writepath( List ).

%listpath adapted from graphpath.pl
listpath( Node, End, [flight( Node, Next, NodeDep)| Outlist] ) :-
   not(Node = End), 
   flight( Node, Next, NodeDep),
   listpath( Next, End, [flight( Node, Next, NodeDep)], Outlist).

listpath( Node, Node, _, []).

listpath( Node, End, [flight(Pdepart, Parrive, PDepTime)|Tried],
   [flight( Node, Next, NodeDep)|List] ) :-
   flight( Node, Next, NodeDep),
   time_for_arrival( flight( Pdepart, Parrive, PDepTime), PArrival),
   overnight_check( flight(Node, Next, NodeDep)),
   valid_time( PArrival, NodeDep),
   Tried1 = append( [flight(Pdepart, Parrive, PDepTime)], Tried),
   not( member( Next, Tried1)),
   not( Next = Parrive),
   listpath( Next, End, [flight( Node, Next, NodeDep)|Tried1], List ).
    


%populate list and print 
fly(Departure, Arrival ) :-
   listpath( Departure, Arrival, List),
   nl,
   writepath(List),
   !.

% error cases
fly( Depart, Depart ) :- 
   write('Please choose a departure and arrival airport'),
   !, fail. 

fly( Arrive, Arrive ) :-
   write('Please choose an arrival and departure airport'),
   !, fail. 
