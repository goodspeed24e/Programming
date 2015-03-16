<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>進銷存管理系統</title>
</head>

<body>
<!-----cellpadding="0"  cellspacing="0" -------->
<table width="847" height="525" border="0"   cellpadding="0"  cellspacing="0">
  <tr  bgcolor="#eaeaea" bordercolor="#CCCCCC">
    <td colspan="2" background="images/head.gif"><p></p><p><font  color="#999966" size="+4">&nbsp;進銷存</font><font size="+2" color="#CC9966">管理系統</font></p>
	
	<p></p>
    <p><a href="index_2.php?Select=10"> 首頁</a> 客戶管理 報價作業 廠商管理 採購管理 庫存管理 進貨作業 銷售管理 <a href="index_2.php?Select=65">系統設定</a></p></td>
     <?php
	include("mysqlcntdb.php");
	if (empty($Select)) { 
		$Select=10;
	}
	?> 
  
  
  
  </tr>
  <!--valign="top"  ---->
  <tr bgcolor="#666666" valign="top">
    <td width="116" height="396" background="images/menu.gif" >
	 <?php     if ($Select==65) {
		            include("code/code.htm");
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
    <td width="721">
	<?php     if ($Select==650) {	
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
  <tr  bgcolor="#eaeaea" bordercolor="#CCCCCC">
    <td colspan="2"><?php include("copyright.php"); ?>
</td>
  </tr>
</table>
</body>
</html>
