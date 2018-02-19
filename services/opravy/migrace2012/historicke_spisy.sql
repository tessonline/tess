

select id,cislo_jednaci1,cislo_jednaci2 from posta_stare_zaznamy where cislo_spisu2=2010 and cislo_spisu1=68933;


insert into posta (select * from posta_stare_zaznamy where id in ( select id from posta_stare_zaznamy where cislo_spisu1=68933 and cislo_spisu2=2010));
update posta set main_doc=1 where cislo_spisu1=68933 and cislo_spisu2=2010;

--spustit posta_spisy_historie (ale opravit tam potrebne cj)

update posta set cislo_spisu2=cislo_jednaci2,cislo_spisu1=cislo_jednaci1 where cislo_spisu1=68933 and cislo_spisu2=2010;



