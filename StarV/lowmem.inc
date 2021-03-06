
// procedure nosound;assembler;
// asm {
//       lda #0
//       sta $d208
//       sta $d218

//       ldy #3
//       sty $d20f
//       sty $d21f

//       ldy #8
//   lp  sta $d200,y
//       sta $d210,y
//       dey
//       bpl lp
// };
// end;

procedure nosound;
begin
  poke($D200+1,0);
  poke($D202+1,0);
  poke($D204+1,0);
  poke($D206+1,0);
end;

procedure pic_openfile(mynum: Byte);

const
  myname = 'LOC';

begin
  tstr:='';
  if (mynum < 10) then tstr:=concat(myname,'0')
  else tstr:=myname;

  tstr:=concat(tstr,inttostr(mynum));
  tstr:=concat(tstr,'   DAT');

  if xBiosCheck = 0 then
  begin
    CRT_GotoXY(0,5);
    CRT_Write(strings[25]); // no xBios
  end
  else begin
    xBiosOpenFile(tstr);
  end;

end;

procedure pic_load(num: Byte);
begin
  if not disablemusic then
  begin
    music:= false;
    waitframe;
    msx.pause; // interrupt_play;
    nosound;
  end;

  pic_openfile(num);
  // else pic_openfile('GFX',num);
  //if (xBiosCheck = 1) and (xBiosIOresult = 0) then
  if (xBiosCheck <> 0) and (xBiosIOresult = 0) then
  begin
    xBiosLoadLz4Data(Pointer(GFX_ADDRESS));
    // xBiosFlushBuffer;
  end;
  music_restart;
end;

procedure navi_ftljump(distance: Word);

begin
  CRT_ClearRow(7);
  for y:=0 to MAXAVAILABLEDESTINATIONS-1 do
  begin
    CRT_GotoXY(20,0+y); // liststart
    WriteSpaces(18); // clear rows
  end;

  sfx_play(236,202); // vol 10

  gfx_fadeout(false);
  waitframe;
  pic_load(newLoc);
  

  // simulate travel
  repeat
    Dec(distance);
    if (distance mod 5 = 0) then Dec(ship.qf);
    navi_distanceUpdate(distance);
    waitframes(ship.swait);
  until (distance = 0);
  
  randomEncounter;
  calculateprices;
  player.loc:=newLoc;
  if (ship.sindex >= WINSHIP) and (player.uec >= WINUEC) then current_menu:=MENU_CONGRATS
  else current_menu:=MENU_MAIN;
end;