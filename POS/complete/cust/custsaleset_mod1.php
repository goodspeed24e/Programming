<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base進銷存管理系統</title>
</head>
<body>
<?php
// -------------取出所有客戶的資料---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM cust";
	$res = mysql_query($SQLStr);
	
//--------------計算總筆數及頁數------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!------ 傳給 mod2.php 檔案,更新資料表頁面功能  ------>
<form name="form1" method="post" action="cust/custsaleset_mod2.php?custno='$custno'">

  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF" > 
      <td align="center">
<?php
//--------------頁數選擇呈現及連接---------------
     echo "修改客戶銷售設定資料&nbsp;&nbsp; 第&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=112&page=$i>$i</a>|";
	}
       echo "頁, 共".$total."筆&nbsp;&nbsp";
?>
      </td>      
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="1" align="center" bgcolor="#FFFFFF">
          <tr >                     
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
//--------------選擇頁數修改客戶銷售設定資料呈現及連接修改頁面功能-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from cust order by custno  limit $first , 10";
	  $res = mysql_query($SQLStr);	 
      while (list($custno, $custname,  $custsname,  $custleader,  $custinvoice,  $custcontact,  $custtel,  $custmobil,  $custfax,  $custtype,  $custsales,  $custadr,  $custpradr,  $custinadr,  $custemail,  $custhttp,  $custdate,  $custclosdate,  $custprictype,  $custpricper,  $custprepamt,  $custsaleamt,  $custchkamt,  $custprepdc,  $custsaledc,  $custchkdc)=mysql_fetch_row($res))
		{
			echo "<tr bgcolor='#FFFFFF'>			
			         <td align='center'>" .$custno. "</td>\n
			         <td align='center'><a href='cust/custsaleset_mod2.php?custno=" .$custno. "'>" .$custname. "</a></td>\n
			         <td align='center'>" . $custinvoice. "</td>\n
			         <td align='center'>" . $custadr. "</td>\n	
			      </tr>";
		}	
?>         
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>
