<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php 
    // -------------���X������w�P�⪺���---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM  quotationwork WHERE quwksqty  > 0";
	$res = mysql_query($SQLStr);
    //--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!------ �����j�M,�ǵ��D�ؿ�------>
<form name="form1" method="post" action="index.php?Select=10">

  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
		 <?php
    //--------------���ƿ�ܧe�{�γs��---------------
     echo "�Ȥ�q�ʸ��&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=160&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
?> 
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="1" align="center" bgcolor="#FFFFFF">
          <tr>                     
            <td bgcolor="#99CCFF" align="center"> 
             �����渹
            </td>
			 <td bgcolor="#99CCFF" align="center"> 
             �Ȥ�s��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             ���~�s��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              �����ƶq
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              ���
            </td> 
			<td bgcolor="#99CCFF" align="center"> 
              �������
            </td>              
          </tr>		  
	<?php
      //--------------��ܭ��Ƴ����w�P���Ƨe�{�γs�������\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from quotationwork WHERE quwksqty > 0 limit $first , 10";
	  $res = mysql_query($SQLStr);	
       while (list($quwkno, $quwkprod, $quwkcust, $quwktype, $quwkpric, $quwkqty, $quwksqty,$quwksdate)=mysql_fetch_row($res))
		{
		//-------------- ��������w�P���ƪ���ƨçe�{----------------
            echo "<tr border='0'   bgcolor='#ffffff'>";	
			echo "<td align='center'>" . $quwkno  . "</td>\n";
			echo "<td align='center'>" . $quwkcust  . "</td>\n";
			echo "<td align='center'>" . $quwkprod . "</td>\n";
			echo "<td align='center'>" . $quwkqty . "</td>\n";	
			echo "<td align='center'>" . $quwkpric . "</td>\n";				
			echo "<td align='center'>" . $quwksdate . "</td>\n";	
			echo "</tr>";		  	
		}	
?> 
       <tr>
	   <td colspan="6" align="center"><input name="closewindows"  type="submit"  value="����"></td>
	   </tr>    
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>
