<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php
// -------------取出所有廠商的資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM vend";
	$res = mysql_query($SQLStr);
	
//--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<form name="form1" method="post" action="vend/vendbasic_inq2.php">

  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr> 
      <td align="center" bgcolor="#99CCFF">
<?php
//--------------頁數選擇呈現及連接---------------
     echo "搜尋廠商資料&nbsp;&nbsp; 第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=206&page=$i>$i</a>|";
	}
       echo "頁, 共".$total."筆&nbsp;&nbsp";
?>
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr > 
      <td> 
        <table width="782" border="1" align="center"  bgcolor="#FFFFFF">
          <tr>                     
            <td bgcolor="#99CCFF" align="center"> 
              序號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
            名稱
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             統一編號
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              公司地址
            </td>             
          </tr>
<?php
//--------------選擇頁數廠商資料呈現及連接頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from vend order by vendno  limit $first , 10";
	  $res = mysql_query($SQLStr);	 
//----------------取出符合條件資料,搜尋廠商資料,將符合資料取出----------------------	
      while (list($vendno, $vendname,  $vendsname,  $vendleader,  $vendinvoice,  $vendcontact,  $vendtel,  $vendmobil,  $vendfax,  $vendtype,  $vendsales,  $vendadr,  $vendpradr,  $vendinadr,  $vendemail,  $vendhttp,  $venddate,  $vendclosdate,  $vendprictype,  $vendpricper,  $vendprepamt,  $vendsaleamt,  $vendchkamt,  $vendprepdc,  $vendsaledc,  $vendchkdc)=mysql_fetch_row($res))
		{
			echo "<tr border='0'   bgcolor='#ffffff'>";			
			echo "<td align='center'>" .$vendno. "</td>\n";
//-----------------連接vendbasic_inq2-------------------			
			echo "<td align='center'><a href='vend/vendbasic_inq2.php?vendno=" .$vendno. "'>" .$vendname. "</a></td>\n";
			echo "<td align='center'>" . $vendinvoice. "</td>\n";
			echo "<td align='center'>" . $vendadr. "</td>\n";	
			echo "</tr>";
		}	
?>         
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>
