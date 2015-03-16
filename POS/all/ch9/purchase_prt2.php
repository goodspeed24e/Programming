<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body  onLoad="window.print()">
<?php 
    // -------------從採購主資料表,取出符合採購單號的資料---------------
	include("mysqlcntdb.php");	
	$SQLStr = "SELECT * FROM purchmst  WHERE ( purcmtranno = '$purchtranno')";	
	
	$res = mysql_query($SQLStr);	
    //--------------計算總筆數及頁數------------------
    if (mysql_num_rows($res)>0)	
	{
	$row=mysql_fetch_row($res);		
?>
<!------ 完成列印,傳給主目錄------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="604" border="0" align="center" cellspacing="0" cellpadding="0" >
    <tr > 
      <td    align="left"><font size="-1"> 
<?php
     //--------------頁數選擇呈現及連接---------------
     echo "採購單<br>";	
	 echo "採購單號:".$purchtranno."&nbsp;&nbsp;供應廠商:".$purcmvend."/". $purcmvendname  ."&nbsp;&nbsp;交貨日期:".$purcmdate."&nbsp;&nbsp;採購類別:".$purcmtype."<br> ";	
	
?>
    </font></td>
    </tr>
  </table>
  <table width="601" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td width="601"> 
        <table width="595" border="0" align="center" >
		    <tr> 
            <td  align="left" colspan="4"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>
          <tr>                     
            <td width="111"  align="left"><font size="-1">  
             產品編號</font>
            </td>
            <td width="210"  align="left"><font size="-1">  
              產品名稱</font>
            </td>
            <td width="161"  align="left"><font size="-1">  
              採購數量</font>
            </td>
            <td width="95" align="left"><font size="-1">  
              單價</font>
            </td>             
          </tr>	
		    <tr> 
            <td  align="left" colspan="4"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>	  
	<?php
      //--------------選擇頁數銷貨單資料呈現及連接頁面功能-----------	 
	  $SQLStr="select * from purchase where  purchtranno =  '$purchtranno' ";
	  $res = mysql_query($SQLStr);	

       while (list($purchtranno, $purchprodno, $purchprodqty, $purchinqty, $purchpric, $purchunit, $purchprodname)=mysql_fetch_row($res))
		{
       //---------------採購主資料表,取出符合採購單,抓取資料表中資料並呈現-------
            echo "<tr border='0'   >";	
			echo "<td align='left'><font size='-1'>" . $purchprodno  . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $purchprodname . "</font></td>\n";
			echo "<td align='left'><font size='-1'>" . $purchprodqty . "</font></td>\n";	
			echo "<td align='left'><font size='-1'>" . $purchpric . "</font></td>\n";	
			echo "</tr>";		  	
		}	
?>      
        </table>
      </td>
    </tr>
  </table>    
</form>
<?
}
else
	{	
	 $msg="無此採購單";
	 include("windowsclose.php");
	}
?>
</body>
</html>
	
