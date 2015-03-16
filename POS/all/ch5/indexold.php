<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>進銷存及帳款處理 WEB BASE 系統  日邦資訊開發設計</title>
<style type="text/css">
<!--
.style2 {color: #000000}
body {
	background-color: #0066FF;
}
-->
</style>
</head>

<body>
<table width="989" height="554" border="1" cellpadding="0" cellspacing="0">
  <tr  bordercolor="#CCCCCC" bgcolor="#eaeaea"  >
    <td height="103" colspan="3" background="images/head1.gif"  valign="bottom" align="center"> <span class="style2" > <a href="index.php?Act=10"  >客戶(C)</a> <a href="index.php?Act=15">報價(O)</a> <a href="index.php?Act=20"> 廠商(V)</a> <a href="index.php?Act=25">採購(P)</a><a href="index.php?Act=30"> 庫存(I)</a><a href="index.php?Act=35"> 進貨(I)</a><a href="index.php?Act=40"> 銷貨(T)</a> <a href="index.php?Act=50"> 管理報表(R)</a><a href="index.php?Act=55"> 應收帳款(A)</a><a href="index.php?Act=60"> 應付帳款(F)</a><a href="index.php?Act=65"> 檔案(F)</a> <a href="index.php?Act=70">設定(S)</a> 說明(H)
        <?php
	include("swmcntdb.php");
	if (empty($Act)) { 
		$Act=10;
	}
	
	
// 瀏覽次數-- 頭--  cnthead.php + counterbody.php 即成瀏覽次數小程式 
//	 include("swmcnthead.php");   
		

?>
    </span> </td>
  </tr>
  <tr bgcolor="#666666" >
   <td width="118" valign="top"  background="images/menu.gif" >
        <?     if ($Act==10) {
		            include("cust/mwmcust.htm");
				} elseif ($Act==15) {
                	include("quotation/mwmquotation.htm");
				} elseif ($Act==20) {
                	include("vend/mwmvend.htm");
				} elseif ($Act==25) {
                	include("purchase/mwmpurchase.htm");
			    } elseif ($Act==30) {
                	include("inv/mwminv.htm");
				} elseif ($Act==35) {
                	include("ininv/mininv.htm");
				} elseif ($Act==40) {
                	include("outinv/mwmoutinv.htm");
				} elseif ($Act==45) {
                	include(".htm");
				} elseif ($Act==50) {
                	include(".htm");
				} elseif ($Act==55) {
                	include(".htm");
				} elseif ($Act==60) {
                	include(".htm");
				} elseif ($Act==65) {
                	include("code/mwmfile.htm");
				} elseif ($Act==70) {
                	include("mwmset.htm"); 					
				} elseif ($Act>=100 and $Act<=109) {
                	include("cust/mwmcustbasic.htm");
				} elseif ($Act>=110 and $Act<=119) {
                	include("cust/mwmcustsaleset.htm");	
				} elseif ($Act>=120 and $Act<=129) {
                	include("cust/mwmcustsaleamt.htm");		
				} elseif ($Act>=130 and $Act<=139) {
                	include("cust/mwmcustaccount.htm");
				} elseif ($Act>=140 and $Act<=149) {
                	include("cust/custprt.htm");						
				} elseif ($Act>=150 and $Act<=159) {
                	include("quotation/mwmquotation_cust.htm");
				} elseif ($Act>=160 and $Act<=169) {
                	include("quotation/mwmquotation_price.htm");	
				} elseif ($Act>=170 and $Act<=179) {
                	include("quotation/mwmquotation_send.htm");					
				} elseif ($Act>=200 and $Act<=209) {
                	include("vend/mwmvendbasic.htm");
				} elseif ($Act>=210 and $Act<=219) {
                	include("vend/mwmvendsaleset.htm");	
				} elseif ($Act>=220 and $Act<=229) {
                	include("vend/mwmvendsaleamt.htm");		
				} elseif ($Act>=230 and $Act<=239) {
                	include("vend/mwmvendaccount.htm");					
				} elseif ($Act>=250 and $Act<=259) {
                	include("purchase/mwmpurchase_order.htm");
				} elseif ($Act>=260 and $Act<=269) {
                	include("purchase/mwmpurchaseset.htm");	
				} elseif ($Act>=270 and $Act<=279) {
                	include("purchase/mwmpurchasenodelv.htm");		
				} elseif ($Act>=280 and $Act<=289) {
                	include("purchase/mwmpurchasehaste.htm");
				} elseif ($Act>=300 and $Act<=309) {
                	include("inv/mwminvbasic.htm");				
				} elseif ($Act>=320 and $Act<=329) {
                	include("inv/mwminvqty.htm");		
				} elseif ($Act>=330 and $Act<=339) {
                	include("inv/mwminvadj.htm");
				} elseif ($Act>=340 and $Act<=349) {
                	include("inv/mwminvstock.htm");
				} elseif ($Act>=350 and $Act<=359) {
                	include("ininv/mininvin.htm");
				} elseif ($Act>=360 and $Act<=369) {
                	include("ininv/mininvins.htm");
				} elseif ($Act>=370 and $Act<=379) {
                	include("ininv/mwmininvtype.htm");	
				} elseif ($Act>=380 and $Act<=389) {
                	include("ininv/mwmininvunit.htm");
				} elseif ($Act>=400 and $Act<=409) {
                	include("outinv/moutinvout.htm");
				} elseif ($Act>=410 and $Act<=419) {
                	include("outinv/mwmoutinvtype.htm");	
				} elseif ($Act>=420 and $Act<=429) {
                	include("outinv/mwmoutinvunit.htm");
				} elseif ($Act>=650 and $Act<=659) {
                	include("file/mwmfile_cuty.htm");				
				} elseif ($Act>=660 and $Act<=668) {
                	include("file/mwmfile_prty.htm");
				} elseif ($Act>=669 and $Act<=669) {
                	include("file/mwmfile_prun.htm");
				} elseif ($Act>=6690 and $Act<=6699) {
                	include("file/mwmfile_prun.htm");
				} elseif ($Act>=670 and $Act<=679) {
                	include("file/mwmfile_vety.htm");
				} elseif ($Act>=680 and $Act<=689) {
                	include("file/mwmfile_saty.htm");
				} elseif ($Act==700) {
                	include("mwmset.htm");                    
				} elseif ($Act==101) {              	
                    include("qwmtk.php");
	                include("news.php");
                    include("swmcntbady.php"); 
		}
		?>
    </td>
    <td width="865" bgcolor="" valign="top" >
	<?php 	                    
                if ($Act>=10 and $Act<=99) {
                    include("qwm1.htm");				 
				} elseif ($Act==100) {
                	include("cust/iwmcustbasic_add.php");
			    } elseif ($Act==102) {
                	include("cust/iwmcustbasic_man.php");
				} elseif ($Act==104) {
                	include("cust/iwmcustbasic_del.php");
				} elseif ($Act==106) {
                	include("cust/iwmcustbasic_inq.php");
				} elseif ($Act==108) {
                	include("cust/iwmcustbasic_prt.php");				
			    } elseif ($Act==112) {
                	include("cust/iwmcustsaleset_man.php");				
				} elseif ($Act==116) {
                	include("cust/iwmcustsaleset_sel.php");
				} elseif ($Act==118) {
                	include("cust/iwmcustsaleset_prt.php");				
			    } elseif ($Act==122) {
                	include("cust/iwmcustsaleamt_man.php");				
				} elseif ($Act==126) {
                	include("cust/iwmcustsaleamt_sel.php");
			    } elseif ($Act==132) {
                	include("cust/iwmcustaccount_man.php");				
				} elseif ($Act==136) {
                	include("cust/iwmcustaccount_sel.php");
				} elseif ($Act==142) {
                	include("cust/custdata_prt1.php");
				} elseif ($Act==144) {
                	include("cust/custrpt_prt1.php");
				} elseif ($Act==146) {
                	include("cust/custact_prt1.php");					
				} elseif ($Act==150) {
                	include("quotation/iwmquotationcust_sel.php");
			    } elseif ($Act==152) {
                	include("quotation/iwmquotationcust_man.php");
				} elseif ($Act==154) {
                	include("quotation/iwmquotationcust_del.php");
				} elseif ($Act==156) {
                	include("quotation/iwmquotationcust_inq.php");
				} elseif ($Act==158) {
                	include("quotation/iwmquotationcust_prt.php");
				} elseif ($Act==160) {
                	include("quotation/iwmquotation_sel.php");
			    } elseif ($Act==162) {
                	include("quotation/iwmquotation_man.php");
				} elseif ($Act==164) {
                	include("quotation/iwmquotation_del.php");
				} elseif ($Act==166) {
                	include("quotation/iwmquotation_inq.php");
				} elseif ($Act==168) {
                	include("quotation/quotation_prt1.php");	
				} elseif ($Act==200) {
                	include("vend/iwmvendbasic_add.php");
			    } elseif ($Act==202) {
                	include("vend/iwmvendbasic_man.php");
				} elseif ($Act==204) {
                	include("vend/iwmvendbasic_del.php");
				} elseif ($Act==206) {
                	include("vend/iwmvendbasic_inq.php");
				} elseif ($Act==208) {
                	include("vend/iwmvendbasic_prt.php");				
			    } elseif ($Act==212) {
                	include("vend/iwmvendsaleset_man.php");				
				} elseif ($Act==216) {
                	include("vend/iwmvendsaleset_sel.php");
				} elseif ($Act==218) {
                	include("vend/iwmvendsaleset_prt.php");				
			    } elseif ($Act==222) {
                	include("vend/iwmvendsaleamt_man.php");				
				} elseif ($Act==226) {
                	include("vend/iwmvendsaleamt_sel.php");
			    } elseif ($Act==232) {
                	include("vend/iwmvendaccount_man.php");				
				} elseif ($Act==236) {
                	include("vend/iwmvendaccount_sel.php");
				} elseif ($Act==250) {
                	include("purchase/iwmpurchase_sel.php");
			    } elseif ($Act==252) {
                	include("purchase/iwmpurchase_man.php");
				} elseif ($Act==254) {
                	include("purchase/iwmpurchase_del.php");
				} elseif ($Act==256) {
                	include("purchase/iwmpurchase_inq.php");
				} elseif ($Act==258) {
                	include("purchase/iwmpurchase_prt.php");
			    } elseif ($Act==260) {
                	include("purchase/iwmpurchset_add.php");			
			    } elseif ($Act==262) {
                	include("purchase/iwmpurchset_man.php");	
			    } elseif ($Act==264) {
                	include("purchase/iwmpurchset_del.php");	
				} elseif ($Act==266) {
                	include("purchase/iwmpurchset_inq.php");
				} elseif ($Act==268) {
                	include("purchase/iwmpurchset_prn.php");				
			    } elseif ($Act==272) {
                	include("purchase/purchasenodelv_mod1.php");				
				} elseif ($Act==276) {
                	include("purchase/purchasenodelv_inq1.php");
				} elseif ($Act==278) {
                	include("purchase/purchasenodelv_prt1.php");
			    } elseif ($Act==282) {
                	include("purchase/iwmpurchaseaccount_man.php");				
				} elseif ($Act==286) {
                	include("purchase/iwmpurchaseaccount_sel.php");
				} elseif ($Act==300) {
                	include("inv/iwminvbasic_add.php");
			    } elseif ($Act==302) {
                	include("inv/iwminvbasic_man.php");
				} elseif ($Act==304) {
                	include("inv/iwminvbasic_del.php");
				} elseif ($Act==306) {
                	include("inv/iwminvbasic_inq.php");
				} elseif ($Act==308) {
                	include("inv/iwminvbasic_prt.php");
			    } elseif ($Act==322) {
                	include("inv/iwminvqty_man.php");				
				} elseif ($Act==326) {
                	include("inv/iwminvqty_sel.php");	
				} elseif ($Act==332) {
                	include("inv/iwminvadj_man.php");				
				} elseif ($Act==336) {
                	include("inv/iwminvadj_sel.php");	
				} elseif ($Act==342) {
                	include("inv/iwminvstock_man.php");				
				} elseif ($Act==346) {
                	include("inv/iwminvstock_sel.php");	
				} elseif ($Act==350) {
                	include("ininv/ininvin_add1.php");
			    } elseif ($Act==352) {
                	include("ininv/ininvin_man.php");
				} elseif ($Act==354) {
                	include("ininv/ininvin_del.php");
				} elseif ($Act==356) {
                	include("ininv/ininvin_inq.php");
				} elseif ($Act==358) {
                	include("ininv/ininvin_prt.php");
			    } elseif ($Act==360) {
                	include("ininv/ininvins_add1.php");
			    } elseif ($Act==362) {
                	include("ininv/ininvins_mod1.php");				
				} elseif ($Act==364) {
                	include("ininv/ininvins_del1.php");
				} elseif ($Act==366) {
               	    include("ininv/ininvins_inq1.php");
				} elseif ($Act==368) {
                	include("ininv/ininvins_prt.php");		
			    } elseif ($Act==372) {
                	include("ininv/ininvsaleset_man.php");				
				} elseif ($Act==376) {
                	include("ininv/iwmininvsaleset_sel.php");
				} elseif ($Act==378) {
                	include("ininv/iwmininvsaleset_prt.php");				
			    } elseif ($Act==382) {
                	include("ininv/iwmininvsaleamt_man.php");				
				} elseif ($Act==386) {
                	include("ininv/iwmininvsaleamt_sel.php");
				} elseif ($Act==400) {					
                	include("outinv/outinvout_add1.php");
			    } elseif ($Act==402) {
                	include("outinv/outinvout_mod1.php");
				} elseif ($Act==404) {
                	include("outinv/outinvout_del1.php");
				} elseif ($Act==406) {
                	include("outinv/outinvout_inq1.php");
				} elseif ($Act==408) {
                	include("outinv/iwmoutinvbasic_prt.php");				
			    } elseif ($Act==412) {
                	include("outinv/iwmoutinvsaleset_man.php");				
				} elseif ($Act==416) {
                	include("outinv/iwmoutinvsaleset_sel.php");
				} elseif ($Act==418) {
                	include("outinv/iwmoutinvsaleset_prt.php");				
			    } elseif ($Act==422) {
                	include("outinv/iwmoutinvsaleamt_man.php");				
				} elseif ($Act==426) {
                	include("outinv/iwmoutinvsaleamt_sel.php");
			    } elseif ($Act==432) {
                	include("outinv/iwmoutinvaccount_man.php");				
				} elseif ($Act==436) {
                	include("outinv/iwmoutinvaccount_sel.php"); 
				} elseif ($Act==650) {
                	include("file/iwmfile_cuty.php");
				} elseif ($Act==652) {
                	include("file/iwmfile_cuty_mod.php");
				} elseif ($Act==654) {
                	include("file/iwmfile_cuty_del.php");
				} elseif ($Act==656) {
                	include("file/iwmfile_cuty_inq.php");
				} elseif ($Act==658) {
                	include("file/iwmfile_cuty_prt.php");			
				} elseif ($Act==660) {
                	include("file/iwmfile_prty.php");				
				} elseif ($Act==662) {
                	include("file/iwmfile_prty_mod.php");
				} elseif ($Act==664) {
                	include("file/iwmfile_prty_del.php");
				} elseif ($Act==666) {
                	include("file/iwmfile_prty_inq.php");
				} elseif ($Act==668) {
                	include("file/iwmfile_prty_prt.php");
				} elseif ($Act==6690) {
                	include("file/iwmfile_prun.php");				
				} elseif ($Act==6692) {
                	include("file/iwmfile_prun_mod.php");
				} elseif ($Act==6694) {
                	include("file/iwmfile_prun_del.php");
				} elseif ($Act==6696) {
                	include("file/iwmfile_prun_inq.php");
				} elseif ($Act==6698) {
                	include("file/iwmfile_prun_prt.php");
				} elseif ($Act==670) {
                	include("file/iwmfile_vety.php");
				} elseif ($Act==672) {
                	include("file/iwmfile_vety_mod.php");
				} elseif ($Act==674) {
                	include("file/iwmfile_vety_del.php");
				} elseif ($Act==676) {
                	include("file/iwmfile_vety_inq.php");
				} elseif ($Act==678) {
                	include("file/iwmfile_vety_prt.php");				
				} elseif ($Act==680) {				
                	include("file/iwmfile_saty.php");
				} elseif ($Act==682) {
                	include("file/iwmfile_saty_mod.php");
				} elseif ($Act==684) {
                	include("file/iwmfile_saty_del.php");
				} elseif ($Act==686) {
                	include("file/iwmfile_saty_inq.php");
				} elseif ($Act==688) {
                	include("file/iwmfile_saty_prt.php");				
				} elseif ($Act==700) {
                	include("iwmset.php");				
				} elseif ($Act==752) {
                	include("qabuydoc.htm");
				}
     ?>	
	</td>    
  </tr>
  <tr>
    <td colspan="3" bgcolor="#eaeaea"><?php include("copyrightedd.php"); ?></td>
  </tr>
</table>
</body>
</html>
