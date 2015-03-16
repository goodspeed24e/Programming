<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>Web base 進銷存系統</title>
<style type="text/css">
<!--
.style2 {color: #000000}
body {
	background-color: #0066FF;
}
-->
</style> 
</head>
<!--#EEEEEE  -->
<body>
<table width="983" height="554" border="0" cellpadding="0" cellspacing="0">
  <tr  bgcolor="#eaeaea">
    <td colspan="2" background="images/head.gif" width="983"><p></p><p><font   color="#000000" size="+4">&nbsp;進銷存</font><font size="+2"   color="#333333">管理系統</font></p>
	<p></p>
    <p> <span class="style2" ><a href="index.php?Select=1">首頁</a><a href="index.php?Select=10"  >客戶管理</a> <a href="index.php?Select=15">報價作業</a> <a href="index.php?Select=20"> 廠商管理</a> <a href="index.php?Select=25">採購管理</a><a href="index.php?Select=30"> 庫存管理</a><a href="index.php?Select=35"> 進貨作業</a><a href="index.php?Select=40"> 出貨管理</a> <a href="index.php?Select=65">系統設定</a></p></td>
<?php	
	include("mysqlcntdb.php");
	if (empty($Select)) { 
		$Select=1;
	}
?>
    </span> </td>
  </tr>
  <tr bgcolor="#666666" >
   <td width="118" valign="top" background="images/menu.gif"  >
        <?php  if ($Select==1) {
		            include("home.htm");
                } elseif ($Select==10) {
            		include("cust/cust.htm");		
				} elseif ($Select==15) {
                	include("quotation/quotation.htm");
				} elseif ($Select==20) {
                	include("vend/vend.htm");
				} elseif ($Select==25) {
                	include("purchase/purchase.htm");
			    } elseif ($Select==30) {
                	include("inv/inv.htm");
				} elseif ($Select==35) {
                	include("ininv/ininv.htm");
				} elseif ($Select==40) {
                	include("outinv/outinv.htm");				
				} elseif ($Select==65) {
                	include("code/code.htm");					
				} elseif ($Select>=100 and $Select<=109) {
                	include("cust/custbasic.htm");
				} elseif ($Select>=110 and $Select<=119) {
                	include("cust/custsaleset.htm");	
				} elseif ($Select>=120 and $Select<=129) {
                	include("cust/custsaleamt.htm");		
				} elseif ($Select>=130 and $Select<=139) {
                	include("cust/custaccount.htm");
				} elseif ($Select>=140 and $Select<=149) {
                	include("cust/cust.htm");						
				} elseif ($Select>=150 and $Select<=159) {
                	include("quotation/quotation_price.htm");
				} elseif ($Select>=160 and $Select<=169) {
                	include("quotation/quotation.htm");	
				} elseif ($Select>=170 and $Select<=179) {
                	include("quotation/quotation.htm");
				} elseif ($Select>=180 and $Select<=189) {
                	include("quotation/quotation.htm");	
				} elseif ($Select>=200 and $Select<=209) {
                	include("vend/vendbasic.htm");
				} elseif ($Select>=210 and $Select<=219) {
                	include("vend/vendsupset.htm");	
				} elseif ($Select>=220 and $Select<=229) {
                	include("vend/vendsupamt.htm");		
				} elseif ($Select>=230 and $Select<=239) {
                	include("vend/vendaccount.htm");					
                } elseif ($Select>=240 and $Select<=249) {
                	include("vend/vend.htm");											
				} elseif ($Select>=250 and $Select<=259) {
                	include("purchase/purchase_order.htm");
				} elseif ($Select>=260 and $Select<=269) {
                	include("purchase/purchasemst.htm");	
				} elseif ($Select>=270 and $Select<=279) {
				    include("purchase/purchase.htm");                	
				} elseif ($Select>=280 and $Select<=289) {
				    include("purchase/purchase.htm");                	
				} elseif ($Select>=290 and $Select<=299) {
                	include("purchase/purchase.htm");
				} elseif ($Select>=300 and $Select<=309) {
                	include("inv/invbasic.htm");				
				} elseif ($Select>=320 and $Select<=329) {
                	include("inv/invqty.htm");		
				} elseif ($Select>=330 and $Select<=339) {
                	include("inv/invadj.htm");
				} elseif ($Select>=340 and $Select<=344) {
                	include("inv/inv.htm");
					} elseif ($Select>=345 and $Select<=349) {
                	include("inv/inv.htm");
				} elseif ($Select>=350 and $Select<=359) {
                	include("ininv/ininv.htm");
				} elseif ($Select>=360 and $Select<=369) {
                	include("ininv/ininvins.htm");
				} elseif ($Select>=370 and $Select<=379) {
                	include("ininv/ininv.htm");	
				} elseif ($Select>=380 and $Select<=389) {
                	include("ininv/ininv.htm");
				} elseif ($Select>=400 and $Select<=409) {
                	include("outinv/outinvout.htm");
				} elseif ($Select>=410 and $Select<=419) {
                	include("outinv/outinv.htm");	
				} elseif ($Select>=420 and $Select<=429) {
                	include("outinv/outinv.htm");
				} elseif ($Select>=650 and $Select<=659) {
                	include("code/cuty.htm");				
				} elseif ($Select>=660 and $Select<=668) {
                	include("code/prty.htm");
				} elseif ($Select>=669 and $Select<=669) {
                	include("code/prun.htm");
				} elseif ($Select>=6690 and $Select<=6699) {
                	include("code/prun.htm");
				} elseif ($Select>=670 and $Select<=679) {
                	include("code/vety.htm");
				} elseif ($Select>=680 and $Select<=689) {
                	include("code/saty.htm");				
		}
		?>
    </td>
    <td width="865" bgcolor="" valign="top" >
	<?php 	                    
                if ($Select==1) {
                    include("qwm1.htm");	
				} elseif ($Select>=10 and $Select<=99) {
                	include("qwm1.htm");		 
				} elseif ($Select==100) {
                	include("cust/custbasic_add.php");
			    } elseif ($Select==102) {
                	include("cust/custbasic_man.php");
				} elseif ($Select==104) {
                	include("cust/custbasic_del1.php");
				} elseif ($Select==106) {
                	include("cust/custbasic_inq1.php");
				} elseif ($Select==108) {
                	include("cust/custbasic_prt.php");				
			    } elseif ($Select==112) {
                	include("cust/custsaleset_mod1.php");				
				} elseif ($Select==116) {
                	include("cust/custsaleset_inq1.php");							
			    } elseif ($Select==122) {
                	include("cust/custsaleamt_mod1.php");				
				} elseif ($Select==126) {
                	include("cust/custsaleamt_inq1.php");
			    } elseif ($Select==132) {
                	include("cust/custaccount_man.php");				
				} elseif ($Select==136) {
                	include("cust/custaccount_sel.php");
				} elseif ($Select==142) {
                	include("cust/custdata_prt1.php");
				} elseif ($Select==144) {
                	include("cust/custrpt_prt1.php");
				} elseif ($Select==146) {
                	include("cust/custact_prt1.php");
				} elseif ($Select==148) {
                	include("cust/custarrec_prt1.php");
               	} elseif ($Select==150) {
                	include("quotation/quotation_add1.php");
			    } elseif ($Select==152) {
                	include("quotation/quotation_mod1.php");
				} elseif ($Select==154) {
                	include("quotation/quotation_del1.php");
				} elseif ($Select==156) {
                	include("quotation/quotation_inq1.php");									
				} elseif ($Select==160) {
                	include("quotation/quotationtrace_prt1.php");			    
				} elseif ($Select==170) {
                	include("quotation/quotationorder_prt1.php");					
				} elseif ($Select==180) {
                	include("quotation/quotation_prt1.php");	
				} elseif ($Select==200) {
                	include("vend/vendbasic_add1.php");
			    } elseif ($Select==202) {
                	include("vend/vendbasic_mod1.php");
				} elseif ($Select==204) {
                	include("vend/vendbasic_del1.php");
				} elseif ($Select==206) {
                	include("vend/vendbasic_inq1.php");							
			    } elseif ($Select==212) {
                	include("vend/vendsupset_mod1.php");				
				} elseif ($Select==216) {
                	include("vend/vendsupset_inq1.php");							
			    } elseif ($Select==222) {
                	include("vend/vendsupamt_mod1.php");				
				} elseif ($Select==226) {
                	include("vend/vendsupamt_inq1.php");
			    } elseif ($Select==232) {
                	include("vend/vendaccount_mod1.php");				
				} elseif ($Select==236) {
                	include("vend/vendaccount_inq1.php");	
				} elseif ($Select==242) {
                	include("vend/venddata_prt1.php");
				} elseif ($Select==244) {
                	include("vend/vendrpt_prt1.php");
				} elseif ($Select==246) {
                	include("vend/vendact_prt1.php");
				} elseif ($Select==248) {
                	include("vend/vendaprec_prt1.php");
				} elseif ($Select==250) {
                	include("purchase/purchase_add1.php");
			    } elseif ($Select==252) {
                	include("purchase/purchase_mod1.php");
				} elseif ($Select==254) {
                	include("purchase/purchase_del1.php");
				} elseif ($Select==256) {
                	include("purchase/purchase_inq1.php");	
			    } elseif ($Select==262) {
                	include("purchase/purchmst_mod1.php");	
			    } elseif ($Select==264) {
                	include("purchase/purchmst_del1.php");	
				} elseif ($Select==266) {
                	include("purchase/purchmst_inq1.php");						
			    } elseif ($Select==270) {
                	include("purchase/purchasenodelv_prt1.php");	
			    } elseif ($Select==280) {
                	include("purchase/purchasehaste_prt1.php");					
				} elseif ($Select==290) {
                	include("purchase/purchase_prt1.php");		
				} elseif ($Select==300) {
                	include("inv/invbasic_add1.php");
			    } elseif ($Select==302) {
                	include("inv/invbasic_mod1.php");
				} elseif ($Select==304) {
                	include("inv/invbasic_del1.php");
				} elseif ($Select==306) {
                	include("inv/invbasic_inq1.php");
				} elseif ($Select==308) {
                	include("inv/invbasic_prt1.php");
			    } elseif ($Select==322) {
                	include("inv/invqty_mod1.php");				
				} elseif ($Select==326) {
                	include("inv/invqty_inq1.php");	
				} elseif ($Select==332) {
                	include("inv/invadj_man.php");				
				} elseif ($Select==336) {
                	include("inv/invadj_sel.php");	
				} elseif ($Select==340) {
                	include("inv/invdtl_prt1.php");
				} elseif ($Select==342) {
                	include("inv/invtype_prt1.php");
                } elseif ($Select==345) {
                	include("inv/invproc_prt1.php");
				} elseif ($Select==350) {
                	include("ininv/ininvpur_add1.php");
			    } elseif ($Select==351) {
                	include("ininv/ininvpur_add2.php");				
			    } elseif ($Select==360) {
                	include("ininv/ininvins_add1.php");
  	   		    } elseif ($Select==361) {
                	include("ininv/ininvins_add2.php");
			    } elseif ($Select==362) {
                	include("ininv/ininvins_mod1.php");				
				} elseif ($Select==364) {
                	include("ininv/ininvins_del1.php");
				} elseif ($Select==366) {
               	    include("ininv/ininvins_inq1.php");
				} elseif ($Select==370) {
                	include("ininv/ininvins_prt1.php");
			    } elseif ($Select==380) {
                	include("ininv/ininvrec_prt1.php");	
				} elseif ($Select==400) {					
                	include("outinv/outinvout_add1.php");
			    } elseif ($Select==402) {
                	include("outinv/outinvout_mod1.php");
				} elseif ($Select==404) {
                	include("outinv/outinvout_del1.php");
				} elseif ($Select==406) {
                	include("outinv/outinvout_inq1.php");						
			    } elseif ($Select==410) {
                	include("outinv/outinvdtl_prt1.php");	                				
			    } elseif ($Select==420) {
                	include("outinv/outinvrec_prt1.php");					
			    } elseif ($Select==432) {
                	include("outinv/outinvaccount_man.php");				
				} elseif ($Select==436) {
                	include("outinv/outinvaccount_sel.php"); 
				} elseif ($Select==650) {
                	include("code/cuty_add.php");
				} elseif ($Select==652) {
                	include("code/cuty_mod.php");
				} elseif ($Select==654) {
                	include("code/cuty_del.php");
				} elseif ($Select==656) {
                	include("code/cuty_inq.php");
				} elseif ($Select==658) {
                	include("code/cuty_prt.php");			
				} elseif ($Select==660) {
                	include("code/prty_add.php");				
				} elseif ($Select==662) {
                	include("code/prty_mod.php");
				} elseif ($Select==664) {
                	include("code/prty_del.php");
				} elseif ($Select==666) {
                	include("code/prty_inq.php");
				} elseif ($Select==668) {
                	include("code/prty_prt.php");
				} elseif ($Select==6690) {
                	include("code/prun_add.php");				
				} elseif ($Select==6692) {
                	include("code/prun_mod.php");
				} elseif ($Select==6694) {
                	include("code/prun_del.php");
				} elseif ($Select==6696) {
                	include("code/prun_inq.php");
				} elseif ($Select==6698) {
                	include("code/prun_prt.php");
				} elseif ($Select==670) {
                	include("code/vety_add.php");
				} elseif ($Select==672) {
                	include("code/vety_mod.php");
				} elseif ($Select==674) {
                	include("code/vety_del.php");
				} elseif ($Select==676) {
                	include("code/vety_inq.php");
				} elseif ($Select==678) {
                	include("code/vety_prt.php");				
				} elseif ($Select==680) {				
                	include("code/saty_add.php");
				} elseif ($Select==682) {
                	include("code/saty_mod.php");
				} elseif ($Select==684) {
                	include("code/saty_del.php");
				} elseif ($Select==686) {
                	include("code/saty_inq.php");
				} elseif ($Select==688) {
                	include("code/saty_prt.php");
				}
     ?>	
	</td>    
  </tr>
  <tr bgcolor="#eaeaea">
    <td colspan="2" bgcolor="#eaeaea"><?php include("copyrightedd.php"); ?></td>
  </tr>
</table>
</body>
</html>
