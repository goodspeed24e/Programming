<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php
// -------------���X�Ҧ����~�����---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM product";
	$res = mysql_query($SQLStr);
//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!--���沣�~�򥻸�ƿ�ܫ�,�i�Jinvbasic_del2.php�s�������e�{------->
<form name="form1" method="post" action="inv/invbasic_del2.php">
  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
	  	  <?php
//--------------���ƿ�ܧe�{�γs��---------------
     echo "�R�����~���&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=304&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
?>
   </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="1" align="center" bgcolor="#FFFFFF" >
          <tr> 
		   <td bgcolor="#99CCFF" align="center"> 
             ���~�s��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             ���~�W��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              �W�满��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              �����t��
            </td> 
          </tr>
		  
<?php
//--------------��ܭ��Ʋ��~��Ƨe�{�γs���R�������\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from product order by prodno  limit $first , 10";
	  $res = mysql_query($SQLStr);	
 while (list($prodno, $prodname, $prodtype, $prodvend, $produnit, $prodipric, $prodspric, $prodsave, $prodpqty, $prodnqty, $prodgrap, $prodsdesp, $proddesp, $prodidate, $prododate)=mysql_fetch_row($res))
  {
//-------------------------- �����ƪ���L��ƨçe�{----------------------------------
            echo "<tr border='0'   bgcolor='#ffffff'>";	
			echo "<td align='center'>" . $prodno  . "</td>\n";
			echo "<td align='center'><a href='inv/invbasic_del2.php?prodno=" . $prodno . "'>" . $prodname . "</a></td>\n";
			echo "<td align='center'>";
			if ($prodsdesp == '') 
		         $prodsdesp="�L�W�满��";	        
			echo  $prodsdesp . "</td>\n";			
			echo "<td align='center'>" . $prodvend . "</td>\n";	
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