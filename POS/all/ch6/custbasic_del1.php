<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?
// -------------���X�Ҧ��Ȥ᪺���---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM cust";
	$res = mysql_query($SQLStr);
	
//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>

<!------�i�Jcustbasic_del2.php �N�Ȥ�򥻸�Ʊq��Ʈw���R��---------->
<form name="form1" method="post" action="custbasic_del2.php">
  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">

<?php
//--------------���ƿ�ܧe�{�γs��---------------
     echo "�R���Ȥ���&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=104&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
?>
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="1" align="center"  bgcolor="#FFFFFF">
          <tr bgcolor="#FFFFFF">		                       
            <td bgcolor="#99CCFF" align="center"> 
             �Ǹ�
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             �W��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             �Τ@�s��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             ���q�a�}
            </td>             
          </tr>
<?php
//--------------��ܭ��ƫȤ��Ƨe�{�γs���R�������\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from cust order by custno  limit $first , 10";
	  $res = mysql_query($SQLStr);	
      while (list($custno, $custname,  $custsname,  $custleader,  $custinvoice,  $custcontact,  $custtel,  $custmobil,  $custfax,  $custtype,  $custsales,  $custadr,  $custpradr,  $custinadr,  $custemail,  $custhttp,  $custdate,  $custclosdate,  $custprictype,  $custpricper,  $custprepamt,  $custsaleamt,  $custchkamt,  $custprepdc,  $custsaledc,  $custchkdc)=mysql_fetch_row($res))
		{
			echo "<tr bgcolor='#ffffff'>";			
			echo "<td align='center'>" .$custno. "</td>\n";
			echo "<td align='center'><a href='cust/custbasic_del2.php?custno=" .$custno. "'>" .$custname. "</a></td>\n";
			echo "<td align='center'>" . $custinvoice. "</td>\n";
			echo "<td align='center'>" . $custadr. "</td>\n";	
			echo "</tr>";
		}	
?>
          <tr>            
			<td colspan="4" align="center">
              �b�W����쩳�U��ܱ��R���Ȥ���             
            </td>           
          </tr>
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>
